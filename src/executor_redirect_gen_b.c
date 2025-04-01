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
				&& !gen_redirect_in(&node, --stdins, false))
			|| (node->type == NODE_HEREDOC
				&& !gen_redirect_in(&node, --stdins, true)))
			return (0);
		node = node->right;
	}
	return (1);
}
// Since heredocs are being handled previous to any execution
//   and the user input is being saved into a temporary file,
//   they can now be treated as a simple stdin redirection.
// The temporary file name will be the node's value.
// One can perhaps make it so the temporary file is removed after
//   the "heredoc stdin redirection" has taken place.

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
