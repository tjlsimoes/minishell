/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:10:01 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <strings.h>
#include "libft.h"

void	ft_bzero(void *s, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
}

// static void	print_memory(void *ptr, size_t size)
// {
// 	unsigned char	*p;
// 	size_t			i;

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

// 	printf("Original bzero:\n");
// 	bzero(str1, 5);
// 	printf("String: %s\n", str1);
// 	bzero(arr1, sizeof(int) * 3);
// 	printf("Array: ");
// 	print_memory(arr1, sizeof(arr1));

// 	printf("\nCustom ft_bzero:\n");
// 	ft_bzero(str2, 5);
// 	printf("String: %s\n", str2);
// 	ft_bzero(arr2, sizeof(int) * 3);
// 	printf("Array: ");
// 	print_memory(arr2, sizeof(arr2));

// 	return (0);
// }
