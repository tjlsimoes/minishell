/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:51 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:39 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// // Example functions to use with ft_strmapi
// static char	to_uppercase(unsigned intmak i, char c)
// {
// 	(void)i;  // Unused parameter
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// static char	add_index(unsigned int i, char c)
// {
// 	return (c + i);
// }

// int	main(void)
// {
// 	char	*str;
// 	char	*result;

// 	// Test 1: Convert to uppercase
// 	str = "hello, world!";
// 	result = ft_strmapi(str, &to_uppercase);
// 	if (result)
// 	{
// 		printf("Original: %s\n", str);
// 		printf("Uppercase: %s\n", result);
// 		free(result);
// 	}
// 	else
// 		printf("Memory allocation failed\n");

// 	// Test 2: Add index to each character
// 	str = "abcdef";
// 	result = ft_strmapi(str, &add_index);
// 	if (result)
// 	{
// 		printf("Original: %s\n", str);
// 		printf("Added index: %s\n", result);
// 		free(result);
// 	}
// 	else
// 		printf("Memory allocation failed\n");

// 	// Test 3: NULL string
// 	result = ft_strmapi(NULL, &to_uppercase);
// 	if (!result)
// 		printf("NULL string handled correctly\n");

// 	// Test 4: NULL function
// 	str = "test";
// 	result = ft_strmapi(str, NULL);
// 	if (!result)
// 		printf("NULL function handled correctly\n");

// 	return (0);
// }
