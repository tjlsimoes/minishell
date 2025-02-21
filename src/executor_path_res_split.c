/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res_split.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:03:35 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/21 12:33:46 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return index of next non consecutive char c.
int	split_find_end(char *s, int start, char c)
{
	int	i;

	i = start;
	if (s[i] && s[i] == c)
		return (i + 1);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	alt_count_words(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c && i == 0)
			count++;
		else if (s[i] == c && s[i + 1])
		{
			i = split_find_end(s, i + 1, c);
			count++;
			continue ;
		}
		else if (s[i] != c)
		{
			i = split_find_end(s, i, c);
			count++;
			continue ;
		}
		i++;
	}
	return (count);
}

char	*alt_get_next_word(char **s, char c)
{
	char	*word;
	int		length;
	int		i;

	length = 0;
	length = split_find_end(*s, length, c);
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

int	init_get_path_split(int *words, char ***result, char *s, char c)
{
	*words = alt_count_words(s, c);
	if (*words == 0)
		return (0);
	*result = malloc(sizeof(char *) * (*words + 1));
	if (!s || !result)
		return (0);
	return (1);
}

// Modified split to meet the following requirements
//   of $PATH resolution
// Empty entries (::) or a trailing colon (:) in $PATH mean
//   that Bash considers the current directory (.) as part
//   of $PATH.
// Example: If $PATH=":/usr/bin", Bash searches . first.
// e.g. alt_split("babbb", 'b')
// Returns:
// Output[0]: :
// Output[1]: a
// Output[2]: b
// Output[3]: b
// Note the hardwired nature of output[0] if char c is
//   verified at idx 0 of char *s. It will output, even if
//   char c is something entirely different, the string
//   ":".
char	**get_path_split(char *s, char c)
{
	int		words;
	char	**result;
	int		i;

	if (!init_get_path_split(&words, &result, s, c))
		return (NULL);
	i = -1;
	while (++i < words)
	{
		if (*s && i == 0 && *s == c)
		{
			result[i] = ft_strdup(":");
			if (!result[i])
				return (clear_array_idx(result, i), NULL);
			s++;
			continue ;
		}
		else if (*s && *s == c)
			s++;
		result[i] = alt_get_next_word(&s, c);
		if (!result[i])
			return (clear_array_idx(result, i), NULL);
	}
	result[words] = NULL;
	return (result);
}
