/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:23:19 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:39 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(void)
// {
// 	char			*str1 = "Hello";
// 	char			*str2 = "Hello, World!";
// 	char			*str3 = "Hella";
// 	int				n_values[] = {3, 5, 7, 10};
// 	unsigned int	i;
// 	int				result1;
// 	int				result2;

// 	i = 0;
// 	while (i < sizeof(n_values) / sizeof(n_values[0]))
// 	{
// 		printf("Comparing with n = %d:\n", n_values[i]);

// 		result1 = strncmp(str1, str2, n_values[i]);
// 		result2 = ft_strncmp(str1, str2, n_values[i]);
// 		printf("\"Hello\" vs \"Hello, World!\"\n");
// 		printf("Original strncmp: %d\n", result1);
// 		printf("Custom ft_strncmp: %d\n\n", result2);

// 		result1 = strncmp(str1, str3, n_values[i]);
// 		result2 = ft_strncmp(str1, str3, n_values[i]);
// 		printf("\"Hello\" vs \"Hella\"\n");
// 		printf("Original strncmp: %d\n", result1);
// 		printf("Custom ft_strncmp: %d\n\n", result2);

// 		i++;
// 	}
// 	return (0);
// }
