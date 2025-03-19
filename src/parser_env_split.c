/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:28:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/19 12:36:53 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s) && !inside_word)
		{
			inside_word = 1;
			count++;
		}
		else if (ft_isspace((unsigned char)*s))
			inside_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char const **s)
{
	char	*word;
	int		length;
	int		i;

	length = 0;
	while ((*s)[length] && !ft_isspace((unsigned char)(*s)[length]))
		length++;
	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = (*s)[i];
		i++;
	}
	word[length] = '\0';
	*s += length;
	return (word);
}

char	**split_parser_env(char const *s)
{
	int		words;
	char	**result;
	int		i;

	words = count_words(s);
	result = malloc(sizeof(char *) * (words + 1));
	if (!s || !result)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s && ft_isspace((unsigned char)*s))
			s++;
		result[i] = get_next_word(&s);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
	}
	result[words] = NULL;
	return (result);
}
