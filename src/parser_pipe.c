/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:41:35 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/11 10:33:59 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe_node;

	pipe_node = create_node(NODE_PIPE, "|", -1);
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*parse_pipeline(char **tokens, int *index)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_command(tokens, index);
	if (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) == 0)
	{
		(*index)++;
		right = parse_pipeline(tokens, index);
		return (create_pipe_node(left, right));
	}
	return (left);
}
