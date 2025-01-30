/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:18 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 13:09:22 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Determines if a given token is a redirection operator (<, >, or >>),
// returning a boolean value indicating whether it is a redirect. 
int	is_redirect(char *token)
{
	int i;

	if (!token)
		return (0);
	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	return (ft_strncmp(token + i, "<", 1) == 0 || ft_strncmp(token + i, ">", 1) == 0
		|| ft_strncmp(token + i, ">>", 2) == 0 || ft_strncmp(token + i, "<<", 2) == 0);
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
		printf("Right:\n");
		pretty_print_ast(node->right, indent + 1);
	}
}

void free_tokens(char **tokens)
{
	int i;
	if (!tokens)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
