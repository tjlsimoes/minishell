/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:01 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/27 14:57:23 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a new AST (Abstract Syntax Tree) node with the specified 
// type and value, initializing its left and right children to NULL. 
t_ASTNode	*create_node(t_NodeType type, char *value)
{
	t_ASTNode	*node;

	node = malloc(sizeof(t_ASTNode));
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// temporary function to show how does the logic work
// Recursively prints the structure of the AST, displaying each node's 
// type and value with indentation corresponding to its depth in the tree.
void	print_ast(t_ASTNode *node, int depth)
{
	int			i;
	t_ASTNode	*redir;
	t_ASTNode	*arg;

	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
	{
		print_ast(node->left, depth);
		i = -1;
		while (++i < depth)
			printf("  ");
		printf("Pipe\n");
		print_ast(node->right, depth + 1);
	}
	else if (node->type == NODE_COMMAND)
	{
		i = -1;
		while (++i < depth)
			printf("  ");
		printf("Command: %s\n", node->value);
		arg = node->left;
		while (arg != NULL)
		{
			i = -1;
			while (++i < depth + 1)
				printf("  ");
			printf("Arg: %s\n", arg->value);
			arg = arg->right;
		}
		redir = node->right;
		while (redir != NULL)
		{
			i = -1;
			while (++i < depth + 1)
				printf("  ");
			if (redir->type == NODE_REDIRECT_IN)
				printf("Redirect In: %s\n", redir->value);
			else if (redir->type == NODE_REDIRECT_OUT)
				printf("Redirect Out: %s\n", redir->value);
			else if (redir->type == NODE_REDIRECT_APPEND)
				printf("Redirect Append: %s\n", redir->value);
			redir = redir->right;
		}
	}
	else if (node->type == NODE_ENV_VAR)
	{
		i = -1;
		while (++i < depth + 1)
			printf("  ");
		printf("Env Var: %s\n", node->value);
	}
}

// Recursively free left and right subtrees
// Free the node's value if it exists
// Free the node itself
void	free_ast(t_ASTNode *node)
{
	if (node == NULL)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
		free(node->value);
	free(node);
}
