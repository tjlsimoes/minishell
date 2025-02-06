/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:06:48 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/06 12:09:50 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_value_treat(char **str)
{
	int		eq_idx;
	char	*value;
	char	*key;
	char	quote;

	if (!str || !(*str))
		return (1);
	eq_idx = idx(*str, '=');
	if (eq_idx == -1)
		return (1);
	if ((*str)[eq_idx + 1] == '"')
		quote = '"';
	else if ((*str)[eq_idx + 1] == '\'')
		quote = '\'';
	else
		return (-1);
	if (quote == '\'' || quote == '"')	// Mock conditional
		key = get_env_key(*str);
	value = ft_calloc(1, ft_strlen(*str) - eq_idx - 2);
	ft_strlcpy(value, &((*str)[eq_idx + 2]), ft_strlen(*str) - eq_idx - 2);
	free(*str);
	*str = alt_strjoin(key, "=");
	*str = alt_strjoin(*str, value);
	free(value);
	return (0);
}


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


// Refactor export()
// From NAME="VALUE"
// Get NAME=VALUE
// Be VALUE within double quotes or single quotes.

// Next step:
// Remove all identical quotes if quotes present
//   upon VALUE definition.

// Next step:
// If VALUE within double quotes expand environment
//   variables.
// Also expand if there are no quotes.
// If Value within single quotes do not expand.

// NAME=VALUE
// '=' at idx 4
// Length 10
// 10 - 4 = 6
// Lenght of VALUE = 5

// NAME="VALUE"
// '=' at idx 4
// Length 12
// 12 - 4 = 8
// initial quote idx 5
// final quote idx 11
