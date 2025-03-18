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
		return (def_exit(1),
			report_error(ERROR_OPEN, (*current)->value), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (def_exit(1),
			close(fd_out), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (def_exit(1),
			report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	gen_redirect_append(t_ast_node **current)
{
	int	fd_out;

	fd_out = open((*current)->value, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (fd_out == -1)
		return (def_exit(1),
			report_error(ERROR_OPEN, (*current)->value), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (def_exit(1), close(fd_out),
			report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (def_exit(1),
			report_error(ERROR_CLOSE, (*current)->value), 0);
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
		return (def_exit(1),
			report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*current)->value), 0);
	if (stdins != 0)
		return (close(fd_in), 1);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (def_exit(1),
			close(fd_in), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_in) == -1)
		return (def_exit(1),
			report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}
