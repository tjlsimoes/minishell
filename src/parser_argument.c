/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:23:56 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/07 12:08:40 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ASTNode	*parse_argument_node(char *value, int fd)
{
	int	len;

	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
	{
		value[len - 1] = '\0';
		return (create_node(NODE_ARGUMENT, value + 1, fd));
	}
	return (create_node(NODE_ARGUMENT, value, fd));
}
