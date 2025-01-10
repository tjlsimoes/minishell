/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/05 15:56:38 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (i < size)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	*str1 = "Hello, World!";
// 	const char	*str2 = "Hello, There!";
// 	const char	*str3 = "Hello, World!";
// 	int			len1 = 13;
// 	int			len2 = 5;
// 	int			result1;
// 	int			result2;

// 	printf("Comparing \"%s\" and \"%s\":\n", str1, str2);
// 	result1 = memcmp(str1, str2, len1);
// 	result2 = ft_memcmp(str1, str2, len1);
// 	printf("Standard memcmp: %d\n", result1);
// 	printf("Custom ft_memcmp: %d\n\n", result2);

// 	printf("Comparing \"%s\" and \"%s\" (first %d bytes):\n", str1, str2, len2);
// 	result1 = memcmp(str1, str2, len2);
// 	result2 = ft_memcmp(str1, str2, len2);
// 	printf("Standard memcmp: %d\n", result1);
// 	printf("Custom ft_memcmp: %d\n\n", result2);

// 	printf("Comparing \"%s\" and \"%s\":\n", str1, str3);
// 	result1 = memcmp(str1, str3, len1);
// 	result2 = ft_memcmp(str1, str3, len1);
// 	printf("Standard memcmp: %d\n", result1);
// 	printf("Custom ft_memcmp: %d\n", result2);

// 	return (0);
// }
