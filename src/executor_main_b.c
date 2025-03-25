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

void	alt_attempt_path_res(t_ast_node **ast)
{
	t_ast_node	*node;
	char		*abs_path;

	node = *ast;
	abs_path = path_resolution(node->value);
	if (!abs_path)
		return ;
	sigfree_init(abs_path, true);
	alt_child_exec(abs_path, ast);
	free(abs_path);
}

void	alt_exec_switch(t_ast_node **ast)
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
	{
		sigfree_init(NULL, true);
		builtins_exec(ast);
	}
	else
		alt_attempt_path_res(ast);
}

void	exec_pipe_child_exit(char *error_msg)
{
	child_free(NULL);
	if (error_msg)
		report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
	exit(0);
}

void	exec_pipe_left(t_ast_node **ast, int fd[2])
{
	close(fd[0]);
	if ((*ast)->left->type == NODE_COMMAND && (*ast)->left->value[0] == '\0')
	{
		ft_putstr_fd("Here\n", 2);
		get_sh()->close_stdin = false;
		gen_heredocs(&((*ast)->left));
		exit_shell(0, fd[1], -1);
		return ;
	}
	else if (!has_heredocs(&(*ast)->left))
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
			exit_shell(1, fd[1], -1);
		}
	}
	else
		get_sh()->gen_output = false;
	close(fd[1]);
	alt_exec_switch(&((*ast)->left));
	exit_shell(get_sh()->exit_status, -1, -1);
}

void	exec_pipe_right(t_ast_node **ast, int fd[2])
{
	int	temp_file;

	temp_file = open("/home/pgr/repos/42/minishell/temp_file", O_RDONLY);
	close(fd[1]);
	if ((*ast)->right->type == NODE_COMMAND && (*ast)->right->value[0] == '\0')
	{
		get_sh()->close_stdin = false;
		gen_heredocs(&((*ast)->right));
		exit_shell(0, fd[0], -1);
		return ;
	}
	else if (has_heredocs(&(*ast)->right))
	{
		if (temp_file != -1)
		{
            dup2(temp_file, STDIN_FILENO);
            close(temp_file);
		}
	}
	else if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
		exit_shell(1, -1, fd[0]);
	}
	close(fd[0]);
	if ((*ast)->right->type == NODE_PIPE)
		exec_pipe(&((*ast)->right));
	else
		alt_exec_switch(&((*ast)->right));
	exit_shell(get_sh()->exit_status, -1, -1);
}

// void exec_pipe_right(t_ast_node **ast, int fd[2])
// {
//     close(fd[1]); // Close the write end of the pipe

//     // Ensure the right side gets a valid stdin
//     if (has_heredocs(&(*ast)->right))
//     {
//         int heredoc_fd = open("/tmp/minishell_heredoc", O_RDONLY);
//         if (heredoc_fd != -1)
//         {
//             dup2(heredoc_fd, STDIN_FILENO);
//             close(heredoc_fd);
//         }
//     }
//     else if (dup2(fd[0], STDIN_FILENO) == -1)
//     {
//         report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
//         exit_shell(1, -1, fd[0]);
//     }

//     close(fd[0]);

//     if ((*ast)->right->type == NODE_PIPE)
//         exec_pipe(&((*ast)->right));
//     else
//         alt_exec_switch(&((*ast)->right));

//     exit_shell(get_sh()->exit_status, -1, -1);
// }

