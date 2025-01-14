/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:01 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/14 14:49:34 by asafrono         ###   ########.fr       */
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
	int	i;

	if (node == NULL)
		return ;
	i = -1;
	while (++i < depth)
		printf("  ");
	if (node->type == NODE_COMMAND)
		printf("Command: %s\n", node->value);
	else if (node->type == NODE_PIPE)
	{
		print_ast(node->left, depth + 1);
		if (node->right->type == NODE_PIPE)
			print_ast(node->right, depth);
		else
			print_ast(node->right, depth + 1);
		return ;
	}
	else if (node->type == NODE_REDIRECT_IN)
		printf("Redirect In: %s\n", node->value);
	else if (node->type == NODE_REDIRECT_OUT)
		printf("Redirect Out: %s\n", node->value);
	else if (node->type == NODE_REDIRECT_APPEND)
		printf("Redirect Append: %s\n", node->value);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
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
