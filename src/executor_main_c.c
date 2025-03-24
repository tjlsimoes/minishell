/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 11:55:06 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_heredocs(t_ast_node **ast)
{
	t_ast_node *node;

	if (!ast || (!*ast))
		return (false);
	node = *ast;
	while (node)
	{
		if (node->type == NODE_HEREDOC)
			return (true);
		node = node->right;
	}
	return (false);
}

void	exec_pipe(t_ast_node **ast)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		wstatus;
	void	(*original_sigint)(int);

	if (pipe(fd) == -1)
		return (report_error(ERROR_PIPE, "Failed to create pipe"));
	original_sigint = signal(SIGINT, SIG_IGN);
	pid_left = fork();
	if (pid_left == -1)
		return (report_error(ERROR_FORK, "Failed to fork process"));
	if (pid_left == 0)
		exec_pipe_left(ast, fd);
	if (has_heredocs(&(*ast)->left))
		waitpid(pid_left, NULL, 0);
	pid_right = fork();
	if (pid_right == 0)
		exec_pipe_right(ast, fd);
	close(fd[0]);
	close(fd[1]);
	if (!has_heredocs(&(*ast)->left))
		waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &wstatus, 0);
	signal(SIGINT, original_sigint);
	set_exit_status(wstatus, true);
}

void	simple_command_exec(t_ast_node **ast)
{
	t_ast_node	*node;
	// int			orig_stdin;
	// int			orig_stdout;

	if (!ast || !(*ast))
		return ;
	node = *ast;
	// orig_stdin = dup(STDIN_FILENO);
	// orig_stdout = dup(STDOUT_FILENO);
	if (node->type == NODE_COMMAND && node->value[0] == '\0' && node->right)
	{
		// Need to safeguard against non-heredocs redirections
		get_sh()->close_stdin = false;
		if (!gen_redirections(ast))
			def_exit(1);
	}
	else if (node->type == NODE_COMMAND)
		exec_switch(&node);
	else if (node->type == NODE_PIPE)
		exec_pipe(&node);
	// cleanup_proc_fds(orig_stdin, orig_stdout);
	free_ast(*ast);
	*ast = NULL;
}
