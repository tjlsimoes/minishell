/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:50 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

void	*ft_memset(void *b, int c, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)b;
	i = 0;
	while (i < size)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// static void	print_memory(void *ptr, int size)
// {
// 	unsigned char	*p;
// 	int				i;

// 	p = (unsigned char *)ptr;
// 	i = 0;
// 	while (i < size)
// 	{
// 		printf("%02x ", p[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// int	main(void)
// {
// 	char	str1[20] = "Hello, World!";
// 	char	str2[20] = "Hello, World!";
// 	int		arr1[5] = {1, 2, 3, 4, 5};
// 	int		arr2[5] = {1, 2, 3, 4, 5};

// 	printf("Original memset:\n");
// 	memset(str1, '*', 5);
// 	printf("String: %s\n", str1);
// 	memset(arr1, 0, sizeof(int) * 3);
// 	printf("Array: ");
// 	print_memory(arr1, sizeof(arr1));

// 	printf("\nCustom ft_memset:\n");
// 	ft_memset(str2, '*', 5);
// 	printf("String: %s\n", str2);
// 	ft_memset(arr2, 0, sizeof(int) * 3);
// 	printf("Array: ");
// 	print_memory(arr2, sizeof(arr2));

// 	return (0);
// }
