/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:53:57 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 11:07:24 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to attach a node to the command node's left or right
void	attach_node(t_ASTNode *cmd_node, t_ASTNode *new_node)
{
	t_ASTNode	*current;

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

void	expand_env_variable(char **token)
{
	char		*var_value;
	char		*key;
	char		*not_name;

	not_name = get_non_var(*token + 1);
	if (not_name)
	{
		key = ft_calloc(1, not_name - *token);
		ft_strlcpy(key, *token + 1, not_name - *token);
		not_name = ft_strdup(not_name);
	}
	else
		key = ft_strdup(*token + 1);
	free(*token);
	*token = NULL;
	var_value = get_env_value(get_env_pair(&(get_minishell()->env_var), key));
	if (not_name)
	{
		*token = alt_strjoin(var_value, not_name);
		free(not_name);
	}
	else
		*token = var_value;
	free(key);
}
// Note that in case of not_name != NULL, var_value will be freed
// from within alt_strjoin.

void	parse_env_variable(char **tokens, int *index, t_ASTNode *cmd_node)
{
	t_ASTNode	*arg_node;

	expand_env_variable(&(tokens[*index]));
	arg_node = create_node(NODE_ARGUMENT, tokens[*index], -1);
	(*index)++;
	attach_node(cmd_node, arg_node);
}
// Note that var_value is twice allocated: within node creation and
// within expand_env_variable()'s get_env_value().   

// Parses a sequence of tokens to construct a command node in the AST,
// updating the index to reflect the position in the token array.
// t_ASTNode	*parse_command(char **tokens, int *index)
// {
// 	t_ASTNode	*cmd_node;
// 	t_ASTNode	*arg_node;

// 	cmd_node = create_node(NODE_COMMAND, tokens[*index], -1);
// 	(*index)++;
// 	while (tokens[*index] != NULL && ft_strncmp(tokens[*index], "|", 2) != 0)
// 	{
// 		if (is_redirect(tokens[*index]))
// 			parse_redirect_node(tokens, index, cmd_node);
// 		else if (tokens[*index][0] == '$')
// 			parse_env_variable(tokens, index, cmd_node);
// 		else
// 		{
// 			arg_node = create_node(NODE_ARGUMENT, tokens[*index], -1);
// 			(*index)++;
// 			attach_node(cmd_node, arg_node);
// 		}
// 	}
// 	return (cmd_node);
// }

t_ASTNode	*parse_command(char **tokens, int *index)
{
	t_ASTNode	*cmd_node;
	t_ASTNode	*arg_node;
	bool		cmd_initialized;

	cmd_node = NULL;
	cmd_initialized = false;
	while (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) != 0)
	{
		if (is_redirect(tokens[*index]))
		{
			if (!cmd_initialized)
				cmd_node = create_node(NODE_COMMAND, "", -1);
			parse_redirect_node(tokens, index, cmd_node);
			cmd_initialized = true;
		}
		else if (!cmd_initialized)
		{
			cmd_node = create_node(NODE_COMMAND, tokens[(*index)++], -1);
			cmd_initialized = true;
		}
		else if (tokens[*index][0] == '$')
			parse_env_variable(tokens, index, cmd_node);
		else
		{
			arg_node = create_node(NODE_ARGUMENT, tokens[(*index)++], -1);
			attach_node(cmd_node, arg_node);
		}
	}
	if (!cmd_initialized)
		return (NULL);
	return (cmd_node);
}

t_ASTNode	*parse_pipeline(char **tokens, int *index)
{
	t_ASTNode	*left;
	t_ASTNode	*right;
	t_ASTNode	*pipe_node;

	left = parse_command(tokens, index);
	if (tokens[*index] && ft_strncmp(tokens[*index], "|", 2) == 0)
	{
		(*index)++;
		right = parse_pipeline(tokens, index);
		pipe_node = create_node(NODE_PIPE, "|", -1);
		pipe_node->left = left;
		pipe_node->right = right;
		return (pipe_node);
	}
	return (left);
}

t_ASTNode	*parse(char **tokens)
{
	int	index;

	index = 0;
	return (parse_pipeline(tokens, &index));
}
