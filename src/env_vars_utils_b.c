/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:49:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 12:13:46 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get index of non-NULL character c within parameter str.
int	idx(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (*str)
	{
		if (*str == (char)c)
			return (i);
		i++;
		str++;
	}
	return (-1);
}

void	free_node(t_list **node_adrr)
{
	t_list	*node;

	node = *node_adrr;
	free(node->content);
	free(node);
	node = NULL;
}

char	*alt_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	i = ft_strcpy(str, (char *)s1, i);
	i = ft_strcpy(str, (char *)s2, s1_len);
	str[i] = '\0';
	if (s1_len > 0)
		free(s1);
	return (str);
}

int	ft_strcpy(char *str, char *s, int start)
{
	int		i;

	i = start;
	if (s)
	{
		while (s[i - start] != '\0')
		{
			str[i] = s[i - start];
			i++;
		}
	}
	return (i);
}

// Check if passed env variable NAME (taken here to be synonymous
// to the concept of 'key') matches value passed in str parameter.
// Returns 1 if str == 'NAME' matching environment variable 'NAME=...'
// Otherwise it returns 0.
int	is_key(t_list *env_var, char *str)
{
	int	str_len;

	if (!env_var || !str)
		return (0);
	str_len = ft_strlen(str);
	if (ft_strncmp(env_var->content, str, str_len) == 0
		&& ((char *)env_var->content)[str_len] == '=')
		return (1);
	return (0);
}
