/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:49:57 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:00:41 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
