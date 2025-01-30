/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:41:35 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 16:58:26 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ASTNode	*create_pipe_node(t_ASTNode *left, t_ASTNode *right)
{
	t_ASTNode	*pipe_node;

	pipe_node = create_node(NODE_PIPE, "|", -1);
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ASTNode	*parse_pipeline(char **tokens, int *index)
{
	t_ASTNode	*left;
	t_ASTNode	*right;

	left = parse_command(tokens, index);
	if (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) == 0)
	{
		(*index)++;
		right = parse_pipeline(tokens, index);
		return (create_pipe_node(left, right));
	}
	return (left);
}
