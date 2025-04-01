/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/11 20:37:17 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Main function split into two smaller functions
static t_ast_node	*create_redirect_node(char **tokens, int *index)
{
	t_node_type	redirect_type;
	char		*redirect_s;
	int			op_len;
	int			fd;

	fd = get_redirect_metadata(tokens[*index], &redirect_type,
			&redirect_s, &op_len);
	return (create_redirect_ast_node(tokens, index, redirect_type, fd));
}

t_ast_node	*parse_redirect_node(char **tokens,
				int *index, t_ast_node *cmd_node)
{
	t_ast_node	*redirect_node;
	t_ast_node	**current;

	if (!tokens[*index + 1] || is_redirect(tokens[*index + 1]))
	{
		report_error(ERROR_SYNTAX, tokens[*index + 1]);
		(*index)++;
		return (def_exit(2), NULL);
	}
	redirect_node = create_redirect_node(tokens, index);
	if (!redirect_node)
		return (NULL);
	current = &cmd_node->right;
	while (*current)
		current = &(*current)->right;
	*current = redirect_node;
	return (redirect_node);
}

//IT IS FINE BUT NORMINETTE
// static t_ast_node	*create_redirect_node(char **tokens, int *index)
// {
// 	t_node_type	redirect_type;
// 	char		*redirect_s;
// 	int			op_len;
// 	int			fd;
// 	char		*filename;
// 	t_ast_node	*node;

// 	redirect_type = get_redirect_type(tokens[*index], &redirect_s, &op_len);
// 	fd = parse_redirect_fd(tokens[*index]);
// 	filename = get_filename(tokens, index, redirect_s, op_len);
// 	if (!filename)
// 		return (NULL);
// 	node = create_node(redirect_type, filename, fd);
// 	free(filename);
// 	return (node);
// }
