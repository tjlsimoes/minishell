/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:23:56 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/11 20:28:57 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redirect_index(char *value)
{
	int		i;
	char	quote_char;

	i = -1;
	quote_char = 0;
	while (value[++i] != '\0')
	{
		if (value[i] == '\'' || value[i] == '"')
		{
			if (quote_char == 0)
				quote_char = value[i];
			else if (quote_char == value[i])
				quote_char = 0;
		}
		else if ((value[i] == '<' || value[i] == '>')
			&& (i == 0 || value[i - 1] != '\\') && quote_char == 0)
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
	if (!parse_redirect_node(tokens, &index, node))
		return (free(token_str), free_ast(node), NULL);
	free(token_str);
	return (node);
}

static char	*remove_matching_quotes(char *value)
{
	int		len;
	int		i;
	int		j;
	char	quote_char;
	char	*cleaned_value;

	len = ft_strlen(value);
	cleaned_value = ft_calloc(len + 1, sizeof(char));
	i = 0;
	j = 0;
	quote_char = '\0';
	while (i < len)
	{
		if ((value[i] == '\'' || value[i] == '"') && quote_char == '\0')
			quote_char = value[i];
		else if (value[i] == quote_char)
			quote_char = '\0';
		else
			cleaned_value[j++] = value[i];
		i++;
	}
	cleaned_value[j] = '\0';
	return (cleaned_value);
}

static t_ast_node	*handle_quotes(char *value, int fd)
{
	t_ast_node	*node;
	int			len;
	char		quote_char;
	char		*cleaned_value;

	len = ft_strlen(value);
	quote_char = value[0];
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
	{
		value[len - 1] = '\0';
		node = create_node(NODE_ARGUMENT, value + 1, fd);
		node->quote_char = quote_char;
	}
	else
	{
		cleaned_value = remove_matching_quotes(value);
		node = create_node(NODE_ARGUMENT, cleaned_value, fd);
		free(cleaned_value);
	}
	return (node);
}

t_ast_node	*parse_argument_node(char *value, int fd)
{
	int	redirect_index;

	redirect_index = find_redirect_index(value);
	if (redirect_index != -1)
		return (handle_redirect(value, fd, redirect_index));
	return (handle_quotes(value, fd));
}
