/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:53:57 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/16 17:00:48 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Parses a sequence of tokens to construct a command node in the AST,
// updating the index to reflect the position in the token array. 
t_ASTNode *parse_command(char **tokens, int *index)
{
    t_ASTNode *cmd_node = create_node(NODE_COMMAND, tokens[*index]);
    (*index)++;

    // Add arguments as child nodes
    while (tokens[*index] != NULL && ft_strncmp(tokens[*index], "|", 2) != 0
           && !is_redirect(tokens[*index]))
    {
        t_ASTNode *arg_node = create_node(NODE_ARGUMENT, tokens[*index]);
        if (cmd_node->left == NULL)
            cmd_node->left = arg_node;
        else
        {
            t_ASTNode *current = cmd_node->left;
            while (current->right != NULL)
                current = current->right;
            current->right = arg_node;
        }
        (*index)++;
    }

    return cmd_node;
}



// Identifies and constructs a redirect node (input/output) in the AST
// based on the current token, advancing the index accordingly. 
t_ASTNode	*parse_redirect(char **tokens, int *index)
{
	t_NodeType	type;
	t_ASTNode	*redirect;

	if (ft_strncmp(tokens[*index], "<", 2) == 0)
		type = NODE_REDIRECT_IN;
	else if (ft_strncmp(tokens[*index], ">", 2) == 0)
		type = NODE_REDIRECT_OUT;
	else
		type = NODE_REDIRECT_APPEND;
	(*index)++;
	redirect = create_node(type, tokens[*index]);
	(*index)++;
	return (redirect);
}

// Creates a pipe node in the AST when encountering a pipe token (|),
// incrementing the index to skip over the pipe token. 
t_ASTNode	*parse_pipe(char **tokens, int *index)
{
	t_ASTNode	*pipe;

	pipe = create_node(NODE_PIPE, "|");
	(*index)++;
	(void)tokens;
	return (pipe);
}

// Links two nodes in the AST by creating a new pipe node that
// connects the existing root to a new command node. 
t_ASTNode	*handle_pipe(t_ASTNode *root, t_ASTNode *node)
{
	t_ASTNode	*pipe_node;

	pipe_node = create_node(NODE_PIPE, "|");
	pipe_node->left = root;
	pipe_node->right = node;
	return (pipe_node);
}

// Constructs the entire AST from an array of tokens by iterating through
// them and calling appropriate parsing functions for commands and pipes. 
t_ASTNode	*parse(char **tokens)
{
	int index = 0;
	t_ASTNode *root = NULL;

	while (tokens[index] != NULL)
	{
		t_ASTNode *node = parse_command(tokens, &index);
		
		if (root == NULL)
		{
			root = node;
		}
		else
		{
			t_ASTNode *pipe_node = create_node(NODE_PIPE, "|");
			pipe_node->left = root;
			pipe_node->right = node;
			root = pipe_node;
		}

		if (tokens[index] && ft_strncmp(tokens[index], "|", 2) == 0)
			index++;
	}

	return root;
}


