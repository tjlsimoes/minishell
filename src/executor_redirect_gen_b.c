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

void	heredoc_read(t_ast_node **heredoc_node, int write_end,
	int stdins_rem)
{
	t_ast_node	*heredoc;
	char		*line;

	if (!heredoc_node || !(*heredoc_node))
		return ;
	heredoc = *heredoc_node;
	line = NULL;
	line = readline("> ");
	if (get_sigfree()->interrupted != 0)
		return ;
	while (line && get_sigfree()->interrupted == 0)
	{
		if ((ft_strncmp(line, heredoc->value, ft_strlen(heredoc->value)) == 0
			&& line[ft_strlen(heredoc->value)] == '\0') || get_sigfree()->interrupted != 0)
			break ;
		if (heredoc->quote_char != '\'')
			expand_env_var(&line);
		if (stdins_rem == 0 && get_sh()->gen_output != false)
		{
			write(write_end, line, ft_strlen(line));
			write(write_end, "\n", 1);
		}
		free(line);
		line = NULL;
		if (get_sigfree()->interrupted == 0)
			line = readline("> ");
	}
	free(line);
}
