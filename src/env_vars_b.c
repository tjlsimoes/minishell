/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:07:19 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/15 12:31:22 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_vars(t_list **lst)
{
	t_list	*node;

	if (!lst || !(*lst))
		return ;
	node = *lst;
	while (node)
	{
		write(1, node->content, ft_strlen(node->content));
		write(1, "\n", 1);
		node = node->next;
	}
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
	if (equal_idx <= 1)
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

// Update environment variable if a match with
// its NAME is verified.
// Return 1 if an update is made.
// Return 0 if an update isn't made.
int	update_env_var(t_list **lst, char *content)
{
	t_list	*node;
	char	*key;

	if (!lst || !(*lst))
		return (0);
	node = *lst;
	key = get_env_key(content);
	while (node)
	{
		if (is_key(node, key))
		{
			free(key);
			key = NULL;
			free(node->content);
			node->content = ft_strdup(content);
			return (1);
		}
		node = node->next;
	}
	free(key);
	key = NULL;
	return (0);
}
