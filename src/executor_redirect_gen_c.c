/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen_c.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:50:44 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/27 09:53:03 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	standalone_red_parent(t_ast_node **ast)
{
	int			orig_stdin;
	int			orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	get_sigfree()->orig[0] = orig_stdin;
	get_sigfree()->orig[1] = orig_stdout;
	if (!standalone_gen_redirections(ast))
		return (builtins_close_fds(orig_stdin, orig_stdout));
	builtins_close_fds(orig_stdin, orig_stdout);
}

int	standalone_gen_redirections(t_ast_node **ast)
{
	t_ast_node	*node;

	node = (*ast)->right;
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !mock_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !mock_redirect_append(&node))
			|| (node->type == NODE_REDIRECT_IN
				&& !mock_redirect_in(&node))
			|| (node->type == NODE_HEREDOC && !mock_redirect_in(&node)))
			return (0);
		node = node->right;
	}
	return (1);
}
// Since heredocs are being handled previous to any execution
//   and the user input is being saved into a temporary file,
//   they can now be treated as a simple stdin redirection.
// The temporary file name will be the node's value.

int	mock_redirect_out(t_ast_node **current)
{
	int	fd_out;

	fd_out = open((*current)->value, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_out == -1)
		return (def_exit(errno),
			report_error(ERROR_OPEN, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (def_exit(errno),
			report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	mock_redirect_append(t_ast_node **current)
{
	int	fd_out;

	fd_out = open((*current)->value, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (fd_out == -1)
		return (def_exit(errno),
			report_error(ERROR_OPEN, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (def_exit(errno),
			report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	mock_redirect_in(t_ast_node **current)
{
	int	fd_in;

	fd_in = open((*current)->value, O_RDONLY);
	if (fd_in == -1)
		return (def_exit(errno),
			report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*current)->value), 0);
	if (close(fd_in) == -1)
		return (def_exit(errno),
			report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}
