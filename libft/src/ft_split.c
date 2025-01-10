/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:41:49 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:45 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && !inside_word)
		{
			inside_word = 1;
			count++;
		}
		else if (*s == c)
			inside_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char const **s, char c)
{
	char	*word;
	int		length;
	int		i;

	length = 0;
	while ((*s)[length] && (*s)[length] != c)
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

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;
	int		i;

	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!s || !result)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s && *s == c)
			s++;
		result[i] = get_next_word(&s, c);
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

// int	main(void)
// {
// 	char	**result;
// 	int		i;

// 	// Test 1: Normal case
// 	printf("Test 1:\n");
// 	result = ft_split("Hello world! This is a test.", ' ');
// 	if (result)
// 	{
// 		for (i = 0; result[i] != NULL; i++)
// 		{
// 			printf("%s\n", result[i]);
// 			free(result[i]);
// 		}
// 		free(result);
// 	}

// 	// Test 2: String with consecutive delimiters
// 	printf("\nTest 2:\n");
// 	result = ft_split(",,split,,this,string,", ',');
// 	if (result)
// 	{
// 		for (i = 0; result[i] != NULL; i++)
// 		{
// 			printf("%s\n", result[i]);
// 			free(result[i]);
// 		}
// 		free(result);
// 	}

// 	// Test 3: Empty string
// 	printf("\nTest 3:\n");
// 	result = ft_split("", ',');
// 	if (result)
// 	{
// 		for (i = 0; result[i] != NULL; i++)
// 		{
// 			printf("%s\n", result[i]);
// 			free(result[i]);
// 		}
// 		free(result);
// 	}

// 	// Test 4: String with no delimiters
// 	printf("\nTest 4:\n");
// 	result = ft_split("NoDelimitersHere", ',');
// 	if (result)
// 	{
// 		for (i = 0; result[i] != NULL; i++)
// 		{
// 			printf("%s\n", result[i]);
// 			free(result[i]);
// 		}
// 		free(result);
// 	}

// 	// Test 5: NULL input
// 	printf("\nTest 5:\n");
// 	result = ft_split(NULL, ',');
// 	if (result == NULL)
// 		printf("NULL input handled correctly\n");

// 	return (0);
// }
