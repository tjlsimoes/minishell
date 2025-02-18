/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:23:56 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/18 13:53:12 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redirect_index(char *value)
{
	int	i;

	i = -1;
	while (value[++i] != '\0')
	{
		if ((value[i] == '<' || value[i] == '>')
			&& (i == 0 || value[i - 1] != '\\'))
			return (i);
	}
	return (-1);
}

static t_ast_node	*handle_redirect(char *value, int fd, int redirect_index)
{
	t_ast_node	*node;
	char		*sub_str;
	char		*token_str;
	char		*tokens[2];
	int			index;

	sub_str = ft_substr(value, 0, redirect_index);
	node = create_node(NODE_ARGUMENT, sub_str, fd);
	free(sub_str);
	token_str = ft_strdup(value + redirect_index);
	tokens[0] = token_str;
	tokens[1] = NULL;
	index = 0;
	parse_redirect_node(tokens, &index, node);
	free(token_str);
	return (node);
}

static t_ast_node	*handle_quotes(char *value, int fd)
{
	t_ast_node	*node;
	int			len;

	len = ft_strlen(value);
	value[len - 1] = '\0';
	node = create_node(NODE_ARGUMENT, value + 1, fd);
	node->quote_char = value[0];
	return (node);
}

t_ast_node	*parse_argument_node(char *value, int fd)
{
	int	len;
	int	redirect_index;

	redirect_index = find_redirect_index(value);
	if (redirect_index != -1)
		return (handle_redirect(value, fd, redirect_index));
	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
		return (handle_quotes(value, fd));
	return (create_node(NODE_ARGUMENT, value, fd));
}

// t_ast_node	*parse_argument_node(char *value, int fd)
// {
// 	int			len;
// 	t_ast_node	*node;

// 	len = ft_strlen(value);
// 	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
// 			|| (value[0] == '\'' && value[len - 1] == '\'')))
// 	{
// 		value[len - 1] = '\0';
// 		node = create_node(NODE_ARGUMENT, value + 1, fd);
// 		node->quote_char = value[0];
// 		return (node);
// 	}
// 	return (create_node(NODE_ARGUMENT, value, fd));
// }