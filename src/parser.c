/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:53:57 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/27 14:53:31 by asafrono         ###   ########.fr       */
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

void	parse_redirect_node(char **tokens, int *index, t_ASTNode *cmd_node)
{
	t_NodeType	redirect_type;
	t_ASTNode	*redirect_node;

	if (ft_strncmp(tokens[*index], "<", 2) == 0)
		redirect_type = NODE_REDIRECT_IN;
	else if (ft_strncmp(tokens[*index], ">", 2) == 0)
		redirect_type = NODE_REDIRECT_OUT;
	else if (ft_strncmp(tokens[*index], ">>", 3) == 0)
		redirect_type = NODE_REDIRECT_APPEND;
	else
		return ;
	redirect_node = create_node(redirect_type, tokens[*index + 1]);
	(*index) += 2;
	if (cmd_node->right == NULL)
		cmd_node->right = redirect_node;
	else
		attach_node(cmd_node, redirect_node);
}

void	parse_env_variable(char **tokens, int *index, t_ASTNode *cmd_node)
{
	char		*var_name;
	char		*var_value;
	t_ASTNode	*arg_node;

	var_name = tokens[*index] + 1;
	var_value = getenv(var_name);
	if (var_value != NULL)
		arg_node = create_node(NODE_ARGUMENT, var_value);
	else
		arg_node = create_node(NODE_ARGUMENT, tokens[*index]);
	(*index)++;
	attach_node(cmd_node, arg_node);
}

// Parses a sequence of tokens to construct a command node in the AST,
// updating the index to reflect the position in the token array.
t_ASTNode	*parse_command(char **tokens, int *index)
{
	t_ASTNode	*cmd_node;
	t_ASTNode	*arg_node;

	cmd_node = create_node(NODE_COMMAND, tokens[*index]);
	(*index)++;
	while (tokens[*index] != NULL && ft_strncmp(tokens[*index], "|", 2) != 0)
	{
		if (is_redirect(tokens[*index]))
			parse_redirect_node(tokens, index, cmd_node);
		else if (tokens[*index][0] == '$')
			parse_env_variable(tokens, index, cmd_node);
		else
		{
			arg_node = create_node(NODE_ARGUMENT, tokens[*index]);
			(*index)++;
			attach_node(cmd_node, arg_node);
		}
	}
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
		pipe_node = create_node(NODE_PIPE, "|");
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
