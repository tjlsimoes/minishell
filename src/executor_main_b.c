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

void	alt_attempt_path_res(t_ast_node **ast, int fd_to_close)
{
	t_ast_node	*node;
	char		*abs_path;

	node = *ast;
	abs_path = path_resolution(node->value);
	if (!abs_path)
		return ;
	alt_child_exec(abs_path, ast, fd_to_close);
	free(abs_path);
}

void	alt_exec_switch(t_ast_node **ast, int fd_to_close)
{
	char	*builtins[8];

	builtins[0] = "cd";
	builtins[1] = "pwd";
	builtins[2] = "echo";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	builtins[7] = NULL;
	if (any(builtins, (*ast)->value))
		builtins_exec(ast, fd_to_close);
	else
		alt_attempt_path_res(ast, fd_to_close);
}

void	exec_pipe_child_exit(int fd_to_close, char *error_msg)
{
	close(fd_to_close);
	child_free(NULL);
	if (error_msg)
		report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
	exit(0);
}

void	exec_pipe_left(t_ast_node **ast, int fd[2])
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
		exit_shell(1, fd[1], -1, -1);
	}
	close(fd[1]);
	alt_exec_switch(&((*ast)->left), -1);
	exit_shell(get_sh()->exit_status, -1, -1, -1);
}

void	exec_pipe_right(t_ast_node **ast, int fd[2])
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
		exit_shell(1, -1, fd[0], -1);
	}
	close(fd[0]);
	if ((*ast)->right->type == NODE_PIPE)
		exec_pipe(&((*ast)->right), -1);
	else
		alt_exec_switch(&((*ast)->right), -1);
	exit_shell(get_sh()->exit_status, -1, -1, -1);
}
