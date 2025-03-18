/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:11 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 21:14:07 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gen_redirect_out(t_ast_node **current)
{
	int	fd_out;

	fd_out = open((*current)->value, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_out == -1)
		return (report_error(ERROR_OPEN, (*current)->value), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	gen_redirect_append(t_ast_node **current)
{
	int	fd_out;

	fd_out = open((*current)->value, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (fd_out == -1)
		return (report_error(ERROR_OPEN, (*current)->value), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	gen_redirect_stdout(t_ast_node **ast)
{
	t_ast_node	*node;

	node = (*ast)->right;
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !gen_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !gen_redirect_append(&node)))
			return (0);
		node = node->right;
	}
	return (1);
}

int	gen_redirect_in(t_ast_node **current, int stdins)
{
	int	fd_in;

	fd_in = open((*current)->value, O_RDONLY);
	if (fd_in == -1)
		return (report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*current)->value), 0);
	if (stdins != 0)
		return (close(fd_in), 1);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_in) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

// int	gen_heredoc(t_ast_node **ast, int stdins_rem)
// {
// 	int	fd[2];
// 	int	orig[2];

// 	if (pipe(fd) == -1)
// 		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
// 	orig[0] = dup(STDIN_FILENO);
// 	orig[1] = dup(STDOUT_FILENO);
// 	heredoc_read(ast, fd[1]);
// 	close(fd[1]);
// 	dup2(orig[1], STDOUT_FILENO);
// 	close(orig[0]);
// 	close(orig[1]);
// 	if (stdins_rem == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 	}
// 	else
// 		close(fd[0]);
// 	return (1);
// }

// -------------------------------------------------------------------------
// int	gen_heredoc(t_ast_node **ast, int stdins_rem)
// {
// 	int		fd[2];
// 	char	*line;

// 	if (!ast || !*ast)
// 		return (0);
// 	if (stdins_rem != 0)
// 	{
// 		heredoc_read(ast, &line, STDIN_FILENO, stdins_rem);
// 		return (1);
// 	}
// 	if (pipe(fd) == -1)
// 		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
// 	heredoc_read(ast, &line, fd[1], stdins_rem);
// 	if (close(fd[1]) == -1)
// 		return (close(fd[0]), report_error(ERROR_CLOSE, "pipe write end"), 0);
// 	if (dup2(fd[0], STDIN_FILENO) == -1)
// 		return (close(fd[0]),
// 			report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0);
// 	if (close(fd[0]) == -1)
// 		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
// 	return (1);
// }

int	gen_heredoc(t_ast_node **ast, int stdins_rem)
{
	int			fd[2];

	if (!ast || !(*ast))
		return (0);
	if (stdins_rem != 0)
	{
		heredoc_read(ast, STDIN_FILENO, stdins_rem);
		return (1);
	}
	if (pipe(fd) == -1)
		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
	heredoc_read(ast, fd[1], stdins_rem);
	if (close(fd[1]) == -1)
		return (close(fd[0]), report_error(ERROR_CLOSE, "pipe write end"), 0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]),
			report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0);
	if (close(fd[0]) == -1)
		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
	return (1);
}
