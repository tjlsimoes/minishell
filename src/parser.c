/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:53:57 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/23 13:15:50 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to attach a node to the command node's left or right
void	attach_node(t_ast_node *cmd_node, t_ast_node *new_node)
{
	t_ast_node	*current;

	if (cmd_node->left == NULL)
		cmd_node->left = new_node;
	else
	{
		current = cmd_node->left;
		while (current->right != NULL)
			current = current->right;
		current->right = new_node;
	}
}

bool	initialize_command(t_ast_node *cmd_node, t_ast_node *arg_node)
{
	free(cmd_node->value);
	cmd_node->value = ft_strdup(arg_node->value);
	free_ast(arg_node);
	return (true);
}

void	process_command_tokens(t_ast_node *cmd_node, char **tokens, int *index)
{
	bool		cmd_initialized;

	cmd_initialized = false;
	while (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) != 0)
	{
		if (is_redirect(tokens[*index]))
			parse_redirect_node(tokens, index, cmd_node);
		else if (tokens[*index][0] == '$')
		{
			if (!cmd_initialized && cmd_node->value[0] == '\0')
				cmd_initialized = initialize_command(cmd_node,
					parse_env_variable(tokens, index));
			else
				attach_node(cmd_node, parse_env_variable(tokens, index));
		}
		else
		{
			if (!cmd_initialized && cmd_node->value[0] == '\0')
				cmd_initialized = initialize_command(cmd_node,
					parse_argument_node(tokens[(*index)++], -1));
			else
				attach_node(cmd_node, parse_argument_node(tokens[(*index)++], -1));
		}
	}
}

t_ast_node	*parse_command(char **tokens, int *index)
{
	t_ast_node	*cmd_node;

	cmd_node = create_node(NODE_COMMAND, "", -1);
	process_command_tokens(cmd_node, tokens, index);
	return (cmd_node);
}

t_ast_node	*parse(char **tokens)
{
	int	index;

	index = 0;
	return (parse_pipeline(tokens, &index));
}
