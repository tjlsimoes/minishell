/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:56:10 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 12:57:17 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// From string assumed to contain an environment variable
// - meaning something like "$NAME" - extract
// invalid portion for environment variable referencing.
// e.g. -HELLO in "$PATH-HELLO".
char	*get_non_var(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (ft_isdigit(str[0]))
		return (str);
	while (str[i])
	{
		if ((special_chars(str[i]) || !ft_isalnum(str[i]))
			&& str[i] != '_')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

// Get 'NAME[=value]' from key passed as parameter
// If successful, it returns the environment variable's
// content as a non-allocated string.
// If an error occurs, it returns NULL;
char	*get_env_pair(t_list **env_vars, char *key)
{
	t_list	*node;

	if (!key || !env_vars || !(*env_vars))
		return (NULL);
	node = *env_vars;
	while (node)
	{
		if (is_key(node, key))
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

// Get NAME from 'NAME[=value]' pair
// If successful it returns allocated string 
// in need of being freed elsewhere.
// Note that if 'pair' doesn't include a '='
// it will return NULL.
// If an error occurs, it returns NULL;
char	*get_env_key(char *pair)
{
	int		equal_idx;
	char	*key;

	if (!pair)
		return (NULL);
	equal_idx = idx(pair, '=');
	if (equal_idx <= 1)
		return (NULL);
	key = ft_calloc(1, equal_idx + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, pair, equal_idx + 1);
	return (key);
}

// Get NAME from 'NAME[=value]' pair
// If successful it returns allocated string
//   in need of being freed elsewhere.
// Note that if 'pair' doesn't include a '='
//   it will return 'pair' allocated.
//   Unlike get_env_key()!
// If an error occurs, it returns NULL;
char	*alt_get_env_key(char *pair)
{
	int		equal_idx;
	char	*key;

	if (!pair)
		return (NULL);
	equal_idx = idx(pair, '=');
	if (equal_idx <= 0)
		return (ft_strdup(pair));
	key = ft_calloc(1, equal_idx + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, pair, equal_idx + 1);
	return (key);
}

// Get value from 'NAME[=value]' pair
// If successful it returns allocated string 
// in need of being freed elsewhere.
// If an error occurs, it returns NULL;
char	*get_env_value(char *pair)
{
	int		equal_idx;
	char	*value;
	int		size;
	char	*substr;

	if (!pair)
		return (NULL);
	equal_idx = idx(pair, '=');
	if (equal_idx <= 0)
		return (NULL);
	size = ft_strlen(pair) - equal_idx;
	value = ft_calloc(1, size);
	if (!value)
		return (NULL);
	substr = ft_strchr(pair, '=');
	if (!substr)
		return (NULL);
	ft_strlcpy(value, ++substr, size);
	return (value);
}
