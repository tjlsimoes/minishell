/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:06:48 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/07 11:07:02 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		&& (c == '_' || ft_isalpha(c)))
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
