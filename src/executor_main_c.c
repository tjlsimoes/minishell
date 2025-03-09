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

void	exec_pipe(t_ast_node **ast, int fd_to_close)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		wstatus;

	if (fd_to_close != -1)
		close(fd_to_close);
	if (pipe(fd) == -1)
		return (report_error(ERROR_PIPE, "Failed to create pipe"));
	pid_left = fork();
	if (pid_left == -1)
		return (report_error(ERROR_FORK, "Failed to fork process"));
	if (pid_left == 0)
		exec_pipe_left(ast, fd);
	pid_right = fork();
	if (pid_right == 0)
		exec_pipe_right(ast, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &wstatus, 0);
	set_exit_status(wstatus, true);
}

void	simple_command_exec(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return ;
	node = *ast;
	if (node->type == NODE_COMMAND)
		return (exec_switch(&node));
	else if (node->type == NODE_PIPE && node->right->value
		&& node->right->value[0] == '\0')
		return (exec_switch(&(node->left)));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(&node, -1));
}
