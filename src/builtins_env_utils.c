/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:16 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/19 11:01:48 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_noargs(t_list **lst)
{
	t_list	*node;

	if (!lst)
		return (report_error(ERROR_ENV_WRITE_FAILED, "No environment list"),
			125);
	if (!(*lst))
		return (0);
	node = *lst;
	while (node)
	{
		if (ft_strncmp(node->content, "?=", 2) == 0)
		{
			node = node->next;
			continue ;
		}
		if (print_declare(&node))
			return (125);
		node = node->next;
	}
	return (0);
}

int	print_declare(t_list **node)
{
	char	*key;
	char	*value;

	write(1, "declare -x ", 12);
	if (idx((*node)->content, '=') == -1)
	{
		if (env_write_error(1, (*node)->content))
			return (125);
		return (write(1, "\n", 1), 0);
	}
	key = get_env_key((*node)->content);
	if (env_write_error(1, key) == -1)
		return (free(key), 125);
	value = get_env_value((*node)->content);
	write(1, "=", 1);
	write(1, "\"", 1);
	if (env_write_error(1, value) == -1)
		return (free(key), free(value), 125);
	free(key);
	free(value);
	write(1, "\"", 1);
	write(1, "\n", 1);
	return (0);
}

int	env_write_error(int fd, char *str)
{
	if (write(fd, str,
		ft_strlen(str)) == -1)
		return (report_error(ERROR_ENV_WRITE_FAILED, "Write failed"), 1);
	return (0);
}
