/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_get_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:57:59 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:19:27 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns everything previous to the index of a
// previously identified environment variable
// as an allocated string.
// Example: return HELLO from 'HELLO$HOME'
char	*get_pre_env(char **orig, int env_idx)
{
	char	*pre_env;

	if (!orig || !(*orig) || env_idx == 0)
		return (NULL);
	pre_env = (char *)ft_calloc(1, env_idx + 1);
	if (!pre_env)
		return (NULL);
	ft_strlcpy(pre_env, *orig, env_idx + 1);
	return (pre_env);
}

// Get NAME from string analogous to
// $NAME!Azkaban
char	*get_env_var(char **orig, char **non_var, int env_idx)
{
	int		key_len;
	char	*key;

	if (!orig || !non_var
		|| !(*orig))
		return (NULL);
	if (!(*non_var))
		key_len = ft_strlen(*orig) - env_idx;
	else
		key_len = *non_var - &((*orig)[env_idx]);
	key = (char *)ft_calloc(1, key_len);
	if (!key)
		return (NULL);
	ft_strlcpy(key, &((*orig)[env_idx + 1]), key_len);
	return (key);
}
