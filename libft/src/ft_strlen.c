/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:40 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h> // Include this header for strlen
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

// int	main(void)
// {
// 	char *test1 = "Hello, World!";
// 	char *test2 = "42 School";
// 	char *test3 = "";
// 	int len1;
// 	int len2;

// 	len1 = strlen(test1);
// 	len2 = ft_strlen(test1);
// 	printf("Original string: \"%s\"\n", test1);
// 	printf("Using strlen: %d\n", len1);
// 	printf("Using ft_strlen: %d\n\n", len2);

// 	len1 = strlen(test2);
// 	len2 = ft_strlen(test2);
// 	printf("Original string: \"%s\"\n", test2);
// 	printf("Using strlen: %d\n", len1);
// 	printf("Using ft_strlen: %d\n\n", len2);

// 	len1 = strlen(test3);
// 	len2 = ft_strlen(test3);
// 	printf("Original string: \"%s\"\n", test3);
// 	printf("Using strlen: %d\n", len1);
// 	printf("Using ft_strlen: %d\n", len2);

// 	return (0);
// }
