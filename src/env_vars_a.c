/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:05:06 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/31 12:30:23 by tjorge-l         ###   ########.fr       */
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

char	*strs_join(char **array)
{
	int		i;
	char	*result;

	if (!array || !(*array))
		return (NULL);
	result = NULL;
	result = alt_strjoin(result, array[0]);
	i = 0;
	while (array[i])
	{
		result = alt_strjoin(result, array[i + 1]);
		i++;
	}
	return (result);
}

void	*clear_array(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}

char	*expand_env_vars(char *str, t_list **env_vars)
{
	int		j;
	char	*key;
	char	*non_var;
	char	*result;

	j = 0;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_')
		&& !special_chars(str[j]))
		j++;
	key = ft_calloc(1, j + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, &str[0], j + 1);
	non_var = ft_calloc(1, ft_strlen(str) - j + 1);
	if (!non_var)
		return (free(key), NULL);
	ft_strlcpy(non_var, &str[j], ft_strlen(str) - j + 1);
	result = get_env_value(get_env_pair(env_vars, key));
	result = alt_strjoin(result, non_var);
	free(key);
	free(non_var);
	return (result);
}
// 	printf("Key: |%s|; Value: |%s|; Non-key: |%s|\n", key, result, non_var);

// Function that takes in a string containing only valid
// environment variables and replaces $NAME with the
// respective value if existent.
// Doesn't currently handle $?.
// e.g. doesn't handle consecutive $, permits env vars
//      starting with digits, ...
// Returns array of strings that can then be joined.
// To get single string with expanded environment
// variables simply call strs_join()
// e.g strs_join(env_vars_expansion(str, env_vars));
char	**env_vars_expansion(char *str, t_list **env_vars)
{
	char	**split;
	char	*expanded;
	int		i;

	split = ft_split(str, '$');
	i = 0;
	while (split[i])
	{
		expanded = expand_env_vars(split[i], env_vars);
		if (!expanded)
			return (clear_array(split), NULL);
		free(split[i]);
		split[i] = expanded;
		i++;
	}
	return (split);
}
// i = 0;
// while (split[i])
// 	printf("|%s|\n", split[i++]);

// if (i == 2)
// {
// 	free(expanded);
// 	return (clear_array(split), NULL);
// }
