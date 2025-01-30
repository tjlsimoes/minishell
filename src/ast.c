/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:01 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 14:55:22 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a new AST (Abstract Syntax Tree) node with the specified 
// type and value, initializing its left and right children to NULL. 
t_ASTNode	*create_node(t_NodeType type, char *value, int fd)
{
	t_ASTNode	*node;

	node = malloc(sizeof(t_ASTNode));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->fd = fd; //initialize fd
	node->left = NULL;
	node->right = NULL;
	return (node);
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

void	print_indent(int indent)
{
	if (indent <= 0)
		return;
	printf("  ");
	print_indent(indent - 1);
}

void	print_node(const t_ASTNode *node, int indent)
{
	const char	*node_type_strings[] = {
	"NODE_COMMAND", "NODE_ARGUMENT", "NODE_PIPE",
	"NODE_REDIRECT_IN", "NODE_REDIRECT_OUT",
	"NODE_REDIRECT_APPEND", "NODE_ENV_VAR", "NODE_HEREDOC"
	};
	
	print_indent(indent);
	printf("Type: %s, Value: %s, FD: %d\n",
			  node_type_strings[node->type],
			  node->value ? node->value : "NULL",
			  node->fd);
}

void	pretty_print_ast(const t_ASTNode *node, int indent)
{
	if (!node)
		return;
	print_node(node, indent);

	if (node->left) {
		print_indent(indent);
		printf("Left:\n");
		pretty_print_ast(node->left, indent + 1);
	}

	if (node->right) {
		print_indent(indent);
		if (node->type == NODE_PIPE)
			printf("Right (Pipe):\n");
		else
			printf("Right:\n");
		pretty_print_ast(node->right, indent + 1);
	}
}
