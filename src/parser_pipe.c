/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:41:35 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/14 17:41:56 by asafrono         ###   ########.fr       */
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

	if (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) == 0)
		return (def_exit(2), report_error(ERROR_SYNTAX, "|"), NULL);
	left = parse_command(tokens, index);
	if (!left)
		return (NULL);
	while (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) == 0)
	{
		(*index)++;
		if (!tokens[*index] || ft_strncmp(tokens[*index], "|", 2) == 0)
			return (def_exit(2),
				report_error(ERROR_SYNTAX, "|"), free_ast(left), NULL);
		right = parse_pipeline(tokens, index);
		if (!right)
			return (free_ast(left), NULL);
		left = create_pipe_node(left, right);
	}
	return (left);
}
