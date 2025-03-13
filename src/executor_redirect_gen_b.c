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

int	gen_redirections(t_ast_node **ast)
{
	t_ast_node	*node;
	int			heredoc;

	heredoc = false;
	node = (*ast)->right;
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !gen_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !gen_redirect_append(&node))
			|| (node->type == NODE_REDIRECT_IN && !gen_redirect_in(&node)))
			return (0);
		else if (node->type == NODE_HEREDOC && heredoc == false)
		{
			if (!gen_heredoc(&node))
				return (0);
			heredoc = true;
		}
		node = node->right;
	}
	return (1);
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

void	heredoc_read(t_ast_node **heredoc_node, char **line, int fd[2])
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
		write(fd[1], (*line), ft_strlen((*line)));
		free((*line));
		(*line) = NULL;
		(*line) = alt_gnl(0, heredoc->value);
	}
	free((*line));
}
