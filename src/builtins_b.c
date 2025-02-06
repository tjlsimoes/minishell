/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:55:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/05 16:38:45 by tjorge-l         ###   ########.fr       */
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
		if ((special_chars(key[i]) || !ft_isalnum(key[i]))
			&& key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	export_error(char **env_pair)
{
	ft_putstr_fd("-bash: export: `", 2);
	ft_putstr_fd((*env_pair), 2);
	ft_putstr_fd("` ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
}

int	ft_export(char **str)
{
	int		eq_idx;
	char	*key;

	eq_idx = idx(*str, '=');
	key = alt_get_env_key(*str);
	if (invalid_key(key))
	{
		export_error(str);
		return (free(key), 1);
	}
	free(key);
	if (eq_idx == -1)
		return (0);
	remove_quotes(str);
	add_env_var(&(get_sh()->env_var), *str);
	return (0);
}
// Does not expand environment variables within
//   environment variable to be exported value.

// Returns 0 no matter what, currently.
int	ft_unset(char *env_name)
{
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
		return (125);
	if (!(*lst))
		return (0);
	node = *lst;
	while (node)
	{
		if (write(1, node->content,
				ft_strlen(node->content)) == -1)
			return (125);
		if (write(1, "\n", 1) == -1)
			return (125);
		node = node->next;
	}
	return (0);
}
