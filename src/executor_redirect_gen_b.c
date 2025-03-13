/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:11 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 12:10:21 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gen_redirections_exit(int fd[2])
{
	if (close(fd[1]) == -1)
		return (report_error(ERROR_CLOSE, "pipe write end"), 0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]),
			report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0);
	if (close(fd[0]) == -1)
		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
	return (1);
}

void	gen_redirections_error(int fd[2])
{
	if (close(fd[1]) == -1)
		report_error(ERROR_CLOSE, "pipe write end");
	if (close(fd[0]) == -1)
		report_error(ERROR_CLOSE, "pipe read end");
}

int	gen_redirections(t_ast_node **ast)
{
	t_ast_node	*node;
	int			fd[2];
	int			heredocs;

	if (pipe(fd) == -1)
		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
	node = (*ast)->right;
	heredocs = nbr_heredocs(ast);
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !gen_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !gen_redirect_append(&node))
			|| (node->type == NODE_REDIRECT_IN && !gen_redirect_in(&node)))
			return (gen_redirections_error(fd), 0);
		else if (node->type == NODE_HEREDOC)
			{
				if (!gen_heredoc(&node, fd[1], --heredocs))
					return (gen_redirections_error(fd), 0);
			}
		node = node->right;
	}
	return (gen_redirections_exit(fd));
}

int	nbr_heredocs(t_ast_node **ast)
{
	t_ast_node	*node;
	int			i;

	node = (*ast)->right;
	i = 0;
	while (node)
	{
		if (node->type == NODE_HEREDOC)
			i++;
		node = node->right;
	}
	return (i);
}

// void	error_gen_red_in(int last_fd, t_ast_node **ast)
// {
// 	if (last_fd != -1)
// 		close(last_fd);
// 	get_sh()->exit_status = 1;
// 	set_exit_status(-1, false);
// 	report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*ast)->value);
// }
// //all redirections should fail immediately on the first error.
// That will pass TEST 60 now.
// int		gen_redirect_in(t_ast_node **ast)
// {
// 	t_ast_node	*node;
// 	int			fd_in;
// 	int			last_valid_fd;

// 	node = (*ast)->right;
// 	last_valid_fd = -1;
// 	while (node)
// 	{
// 		if (node->type == NODE_REDIRECT_IN)
// 		{
// 			fd_in = open(node->value, O_RDONLY);
// 			if (fd_in == -1)
// 				return (error_gen_red_in(last_valid_fd, &node), 0);
// 			if (last_valid_fd != -1)
// 				close(last_valid_fd);
// 			last_valid_fd = fd_in;
// 		}
// 		node = node->right;
// 	}
// 	if (last_valid_fd != -1)
// 	{
// 		dup2(last_valid_fd, STDIN_FILENO);
// 		close(last_valid_fd);
// 	}
// 	return (1);
// }

void	heredoc_read(t_ast_node **heredoc_node, char **line, int write_end, int heredocs_rem)
{
	t_ast_node	*heredoc;

	if (!heredoc_node || !(*heredoc_node || !line || !(*line)))
		return ;
	heredoc = *heredoc_node;
	(*line) = alt_gnl(0, NULL);
	while ((*line))
	{
		if (ft_strncmp((*line), heredoc->value, ft_strlen(heredoc->value)) == 0
			&& (*line)[ft_strlen(heredoc->value)] == '\n')
			break ;
		if (heredoc->quote_char == 'N')
			expand_env_var(line);
		if (heredocs_rem == 0)
			write(write_end, (*line), ft_strlen((*line)));
		free((*line));
		(*line) = NULL;
		(*line) = alt_gnl(0, heredoc->value);
	}
	free((*line));
}
