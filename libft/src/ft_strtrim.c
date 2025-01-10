/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:40:17 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:37 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

static int	ft_char_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_char_in_set(s1[end], set))
		end--;
	trimmed = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start <= end)
		trimmed[i++] = s1[start++];
	trimmed[i] = '\0';
	return (trimmed);
}

// int	main(void)
// {
// 	char	*result;

// 	// Test case 1: Normal trimming
// 	result = ft_strtrim("  Hello, World!  ", " ");
// 	printf("Test 1: '%s'\n", result);
// 	free(result);

// 	// Test case 2: Trimming multiple characters
// 	result = ft_strtrim("...Hello, World!...", ".");
// 	printf("Test 2: '%s'\n", result);
// 	free(result);

// 	// Test case 3: No trimming needed
// 	result = ft_strtrim("Hello, World!", " ");
// 	printf("Test 3: '%s'\n", result);
// 	free(result);

// 	// Test case 4: Empty string
// 	result = ft_strtrim("", " ");
// 	printf("Test 4: '%s'\n", result);
// 	free(result);

// 	// Test case 5: All characters to be trimmed
// 	result = ft_strtrim("   ", " ");
// 	printf("Test 5: '%s'\n", result);
// 	free(result);

// 	// Test case 6: NULL input
// 	result = ft_strtrim(NULL, " ");
// 	printf("Test 6: %s\n", result ? result : "NULL");
// 	free(result);

// 	return (0);
// }
