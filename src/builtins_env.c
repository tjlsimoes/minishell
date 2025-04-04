/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:55:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 11:45:45 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_key(char *key)
{
	int	i;

	if (!key || ft_isdigit(key[0]))
		return (1);
	i = 0;
	while (key[i])
	{
		if ((special_chars(key[i]) || key[i] != '_')
			&& !ft_isalnum(key[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(char **str)
{
	int		eq_idx;
	char	*key;
	char	quote;

	quote = 0;
	eq_idx = idx(*str, '=');
	key = alt_get_env_key(*str);
	if (invalid_key(key))
		return (report_error(ERROR_INVALID_IDENTIFIER, *str), free(key), 1);
	free(key);
	if (eq_idx == -1)
		return (add_env_var(&(get_sh()->env_var), *str), 0);
	get_quote(str, &quote);
	remove_quotes(str);
	if (quote == '"' || !quote)
		expand_env_var(str);
	add_env_var(&(get_sh()->env_var), *str);
	return (0);
}
// Does not expand environment variables within
//   environment variable to be exported value.

// Returns 0 no matter what, currently.
int	ft_unset(char *env_name)
{
	if (ft_strncmp(env_name, "?", 1) == 0)
		return (0);
	del_env_var(&(get_sh()->env_var), env_name);
	return (0);
}

// Should be able to unset multiple environment
// variables.
// Only possible fail condition seems to be
// when trying to unset environment variables
// that are read-only. Handling this would require
// running a script within a child process. And
// even then, I'm not sure it would work. As, if
// I'm seeing things correctly, a read-only env var
// in a child process may lose its read-only status.

int	ft_env(t_list **lst)
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
		if (ft_strncmp(node->content, "?=", 2) == 0
			|| idx(node->content, '=') == -1)
		{
			node = node->next;
			continue ;
		}
		if (write(1, node->content,
				ft_strlen(node->content)) == -1)
			return (report_error(ERROR_ENV_WRITE_FAILED, "Write failed"), 125);
		if (write(1, "\n", 1) == -1)
			return (125);
		node = node->next;
	}
	return (0);
}
