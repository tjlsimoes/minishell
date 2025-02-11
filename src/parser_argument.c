/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:23:56 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/11 13:51:13 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_ast_node	*parse_argument_node(char *value, int fd)
{
	int			len;
	t_ast_node	*node;

	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
	{
		value[len - 1] = '\0';
		node = create_node(NODE_ARGUMENT, value + 1, fd);
		node->quote_char = value[0];
		return (node);
	}
	return (create_node(NODE_ARGUMENT, value, fd));
}

// t_ast_node *parse_argument_node(char *value, int fd)
// {
// 	return (parse_quoted_node(value, fd));
// }
