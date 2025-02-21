/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:53:20 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 12:55:34 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Update previously declared quote var
// with string's quote type.
int	get_quote(char **str, char *quote)
{
	int		eq_idx;

	eq_idx = idx(*str, '=');
	if (eq_idx == -1)
		return (0);
	if ((*str)[eq_idx + 1] == '"')
		*quote = '"';
	else if ((*str)[eq_idx + 1] == '\'')
		*quote = '\'';
	else
		return (0);
	return (1);
}

// Remove quotes quotes matching the initial
// quote. Free str and update it to the result.
void	remove_quotes(char **str)
{
	char	quote;
	char	*result;
	char	**split;

	if (!str || !(*str) || !get_quote(str, &quote))
		return ;
	split = ft_split(*str, quote);
	result = strs_join(split);
	clear_array(split);
	free(*str);
	*str = result;
}

int	valid_env_char(char c)
{
	if (!special_chars(c) && !ft_isdigit(c)
		&& (c == '_' || ft_isalpha(c) || c == '?'))
		return (1);
	return (0);
}
// Note that ? passes, right now, as a valid
//  first env_char.

int	env_var_idx(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && valid_env_char(str[i + 1]))
			return (i);
		i++;
	}
	return (-1);
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
