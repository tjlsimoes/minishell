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
	int			stdins;

	node = (*ast)->right;
	stdins = nbr_stdins(ast);
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !gen_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !gen_redirect_append(&node))
			|| (node->type == NODE_REDIRECT_IN
				&& !gen_redirect_in(&node, --stdins))
			|| (node->type == NODE_HEREDOC && !gen_heredoc(&node, --stdins)))
			return (0);
		node = node->right;
	}
	return (1);
}

int	nbr_stdins(t_ast_node **ast)
{
	t_ast_node	*node;
	int			i;

	node = (*ast)->right;
	i = 0;
	while (node)
	{
		if (node->type == NODE_HEREDOC
			|| node->type == NODE_REDIRECT_IN)
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

// void	heredoc_read(t_ast_node **heredoc_node, char **line, int write_end,
// 	int stdins_rem)
// {
// 	t_ast_node	*heredoc;

// 	if (!heredoc_node || !(*heredoc_node || !line || !(*line)))
// 		return ;
// 	heredoc = *heredoc_node;
// 	(*line) = alt_gnl(0, NULL);
// 	while ((*line))
// 	{
// 		if (ft_strncmp((*line), heredoc->value, ft_strlen(heredoc->value)) == 0
// 			&& (*line)[ft_strlen(heredoc->value)] == '\n')
// 			break ;
// 		if (heredoc->quote_char != '\'')
// 			expand_env_var(line);
// 		if (stdins_rem == 0)
// 			write(write_end, (*line), ft_strlen((*line)));
// 		free((*line));
// 		(*line) = NULL;
// 		(*line) = alt_gnl(0, heredoc->value);
// 	}
// 	free((*line));
// }

// void	heredoc_read(t_ast_node **heredoc_node, char **line, int write_fd,
// 		int stdins_rem)
// {
// 	char	*delimiter;

// 	if (!heredoc_node || !*heredoc_node || !line)
// 		return ;
// 	delimiter = (*heredoc_node)->value;
// 	(*line) = readline("> ");
// 	while ((*line))
// 	{
// 		if (ft_strncmp(*line, delimiter, ft_strlen(delimiter)) == 0
// 		&& (*line)[ft_strlen(delimiter)] == '\0')
// 			break;
// 		if ((*heredoc_node)->quote_char != '\'')
// 			expand_env_var(line);
// 		if (stdins_rem == 0)
// 		{
// 			write(write_fd, (*line), strlen(*line));
// 			write(write_fd, "\n", 1);
// 		}
// 		free(*line);
// 		*line = readline("> ");
// 	}
// 	free(*line);
// }

void	heredoc_read(t_ast_node **heredoc_node, char **line, int write_end,
	int stdins_rem)
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
		if (heredoc->quote_char != '\'')
			expand_env_var(line);
		if (stdins_rem == 0)
			write(write_end, (*line), ft_strlen((*line)));
		free((*line));
		(*line) = NULL;
		(*line) = alt_gnl(0, heredoc->value);
	}
	free((*line));
}
