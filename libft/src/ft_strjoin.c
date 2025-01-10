/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:39:05 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:12:11 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + len1, s2);
	return (result);
}

// int	main(void)
// {
// 	const char	*s1;
// 	const char	*s2;
// 	char		*result;

// 	// Test case 1: Normal concatenation
// 	s1 = "Hello, ";
// 	s2 = "World!";
// 	result = ft_strjoin(s1, s2);
// 	printf("Test 1: %s\n", result);
// 	free(result);

// 	// Test case 2: Empty first string
// 	s1 = "";
// 	s2 = "Non-empty";
// 	result = ft_strjoin(s1, s2);
// 	printf("Test 2: %s\n", result);
// 	free(result);

// 	// Test case 3: Empty second string
// 	s1 = "Non-empty";
// 	s2 = "";
// 	result = ft_strjoin(s1, s2);
// 	printf("Test 3: %s\n", result);
// 	free(result);

// 	// Test case 4: Both strings empty
// 	s1 = "";
// 	s2 = "";
// 	result = ft_strjoin(s1, s2);
// 	if (result)
// 	{
// 		printf("Test 4: '%s'\n", result);
// 	}
// 	else
// 	{
// 		printf("Test 4: NULL\n");
// 	}
// 	free(result);

// 	// Test case 5: NULL input (should return NULL)
// 	result = ft_strjoin(NULL, "Test");
// 	if (result)
// 	{
// 		printf("Test 5: %s\n", result);
// 	}
// 	else
// 	{
// 		printf("Test 5: NULL\n");
// 	}
// 	free(result);

// 	return (0);
// }
