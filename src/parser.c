/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:53:57 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/15 19:41:35 by asafrono         ###   ########.fr       */
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

void	process_env_or_argument(t_ast_node *cmd_node, char **tokens,
			int *index, bool *cmd_initialized)
{
	t_ast_node	*new_node;

	if (tokens[*index][0] == '$')
		new_node = parse_env_variable(tokens, index);
	else
		new_node = parse_argument_node(tokens[(*index)++], -1);
	if (new_node->value[0] != '\0')
	{
		if (!(*cmd_initialized) && cmd_node->value[0] == '\0')
		{
			free(cmd_node->value);
			cmd_node->value = ft_strdup(new_node->value);
			add_arg_nodes(&cmd_node, &new_node);
			*cmd_initialized = true;
		}
		else
			attach_node(cmd_node, new_node);
	}
	else
		free_ast(new_node);
}

void	process_command_tokens(t_ast_node *cmd_node, char **tokens, int *index)
{
	bool	cmd_initialized;

	cmd_initialized = false;
	while (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) != 0)
	{
		if (is_redirect(tokens[*index]))
		{
			if (!parse_redirect_node(tokens, index, cmd_node))
				return ;
		}
		else
			process_env_or_argument(cmd_node, tokens, index, &cmd_initialized);
	}
}

t_ast_node	*parse_command(char **tokens, int *index)
{
	t_ast_node	*cmd_node;

	cmd_node = create_node(NODE_COMMAND, "", -1);
	process_command_tokens(cmd_node, tokens, index);
	if (cmd_node->right != NULL)
		return (cmd_node);
	if (cmd_node->value[0] == '\0')
		return (free_ast(cmd_node), NULL);
	return (cmd_node);
}

t_ast_node	*parse(char **tokens)
{
	int	index;

	index = 0;
	return (parse_pipeline(tokens, &index));
}
