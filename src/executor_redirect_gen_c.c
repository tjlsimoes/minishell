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
	int			stdins;

	node = (*ast)->right;
	stdins = nbr_stdins(ast);
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !mock_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !mock_redirect_append(&node))
			|| (node->type == NODE_REDIRECT_IN
				&& !mock_redirect_in(&node, --stdins))
			|| (node->type == NODE_HEREDOC && !gen_heredoc(&node, --stdins)))
			return (0);
		node = node->right;
	}
	return (1);
}

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

int	mock_redirect_in(t_ast_node **current, int stdins)
{
	int	fd_in;

	fd_in = open((*current)->value, O_RDONLY);
	if (fd_in == -1)
		return (def_exit(errno),
			report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*current)->value), 0);
	if (stdins != 0)
		return (close(fd_in), 1);
	if (close(fd_in) == -1)
		return (def_exit(errno),
			report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}
