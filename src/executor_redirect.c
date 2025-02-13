/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:29:39 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/13 11:32:37 by tjorge-l         ###   ########.fr       */
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

char	*get_redirect_in(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return (NULL);
	node = (*ast)->right;
	while (node)
	{
		if (node->type == NODE_REDIRECT_IN)
			return (node->value);
		node = node->right;
	}
	return (NULL);
}

char	*get_append(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return (NULL);
	node = (*ast)->right;
	while (node)
	{
		if (node->type == NODE_REDIRECT_APPEND)
			return (node->value);
		node = node->right;
	}
	return (NULL);
}