/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:57:41 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/11 19:39:46 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirect_out(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return (NULL);
	node = (*ast)->right;
	while (node)
	{
		if (node->type == NODE_REDIRECT_OUT)
			return (node->value);
		node = node->right;
	}
	return (NULL);
}

// char	*get_redirect_in(t_ast_node **ast)
// {
// 	t_ast_node	*node;

// 	if (!ast || !(*ast))
// 		return (NULL);
// 	node = (*ast)->right;
// 	while (node)
// 	{
// 		if (node->type == NODE_REDIRECT_IN)
// 			return (node->value);
// 		node = node->right;
// 	}
// 	return (NULL);
// }

// char	*get_append(t_ast_node **ast)
// {
// 	t_ast_node	*node;

// 	if (!ast || !(*ast))
// 		return (NULL);
// 	node = (*ast)->right;
// 	while (node)
// 	{
// 		if (node->type == NODE_REDIRECT_APPEND)
// 			return (node->value);
// 		node = node->right;
// 	}
// 	return (NULL);
// }

// Get quote removal length.
// Allocate with quote removal length.
// Use same logic to build resultant string.
// Replace original string with new.
t_ast_node	*get_heredoc(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return (NULL);
	node = (*ast)->right;
	while (node)
	{
		if (node->type == NODE_HEREDOC)
		{
			if (node->value[0] == '\'')
				node->quote_char = '\'';
			else if (node->value[0] == '"')
				node->quote_char = '"';
			else
				node->quote_char = 'N';
			alt_rm_quotes(&(node->value));
			return (node);
		}
		node = node->right;
	}
	return (NULL);
}
