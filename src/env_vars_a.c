/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:05:06 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/07 15:42:36 by tjorge-l         ###   ########.fr       */
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

	if (!array || !(*array))
		return (NULL);
	j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}
