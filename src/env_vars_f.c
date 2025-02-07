/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:49:57 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/07 12:08:44 by asafrono         ###   ########.fr       */
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

char	*join_sections(int env_idx, char **str, char **key, char **non_var)
{
	char	*result;
	char	*value_non_var;

	if (env_idx == 0)
	{
		result = alt_strjoin(
				get_env_value(
					get_env_pair(&(get_sh()->env_var), *key)),
				*non_var);
	}
	else
	{
		value_non_var = alt_strjoin(
				get_env_value(
					get_env_pair(&(get_sh()->env_var), *key)),
				*non_var);
		result = alt_strjoin(get_pre_env(str, env_idx), value_non_var);
		free(value_non_var);
	}
	return (result);
}

// Receives an already allocated string.
// Returns same string with all environment
// variables expanded.
// Currently does not expand $?
void	expand_env_var(char	**str)
{
	int		env_idx;
	char	*non_var;
	char	*key;
	char	*result;

	env_idx = env_var_idx(*str);
	if (env_idx == -1)
		return ;
	non_var = get_non_var(&((*str)[env_idx + 1]));
	key = get_env_var(str, &non_var, env_idx);
	result = join_sections(env_idx, str, &key, &non_var);
	free(key);
	free(*str);
	*str = result;
	if (env_var_idx(*str))
		expand_env_var(str);
}
