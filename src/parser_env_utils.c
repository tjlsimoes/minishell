/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:10:50 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/19 12:41:59 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_whitespace(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (true);
		i++;
	}
	return (false);
}

t_ast_node	*env_node_command(char *expanded)
{
	t_ast_node	*new_node;
	char		**split;
	int			i;

	if (has_whitespace(expanded))
	{
		split = split_parser_env(expanded);
		if (!split)
			return (report_error(ERROR_MEMORY_ALLOCATION, NULL),
				create_node(NODE_COMMAND, NULL, -1));
		if (split[0])
			new_node = create_node(NODE_COMMAND, split[0], -1);
		i = 1;
		while (split[i])
			attach_node(new_node, create_node(NODE_ARGUMENT, split[i++], -1));
		clear_array(split);
	}
	else
		new_node = create_node(NODE_COMMAND, expanded, -1);
	return (new_node);
}

void	add_arg_nodes(t_ast_node **cmd_node, t_ast_node **new_node)
{
	t_ast_node	*temp;
	t_ast_node	*temp_b;

	if ((*new_node)->left)
	{
		temp_b = create_node(NODE_ARGUMENT, (*new_node)->left->value, -1);
		attach_node((*cmd_node), temp_b);
		temp = (*new_node)->left;
		while (temp)
		{
			temp_b = create_node(NODE_ARGUMENT, temp->value, -1);
			attach_node((*cmd_node), temp_b);
			temp = temp->right;
		}
	}
	free_ast((*new_node));
}
