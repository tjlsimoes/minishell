/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:48 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (size--)
			*d++ = *s++;
	}
	else
	{
		d += size;
		s += size;
		while (size--)
			*--d = *--s;
	}
	return (dst);
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
// 	char	str[] = "abcdefghijklmnopqrstuvwxyz";
// 	char	str2[] = "abcdefghijklmnopqrstuvwxyz";

// 	printf("Original string: %s\n", str);
// 	printf("Original memory: ");
// 	print_memory(str, strlen(str));

// 	printf("\nStandard memmove:\n");
// 	memmove(str + 4, str, 10);
// 	printf("Result string: %s\n", str);
// 	printf("Result memory: ");
// 	print_memory(str, strlen(str));

// 	printf("\nCustom ft_memmove:\n");
// 	ft_memmove(str2 + 4, str2, 10);
// 	printf("Result string: %s\n", str2);
// 	printf("Result memory: ");
// 	print_memory(str2, strlen(str2));

// 	return (0);
// }
