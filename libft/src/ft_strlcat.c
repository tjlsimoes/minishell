/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:48:32 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:41 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <bsd/string.h>  
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = 0;
	src_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	while (src[src_len])
		src_len++;
	if (dest_len >= size)
		return (size + src_len);
	i = 0;
	while (src[i] && (dest_len + i + 1) < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// int	main(void)
// {
// 	char			dst1[20] = "Hello, ";
// 	char			dst2[20] = "Hello, ";
// 	char			src[] = "World!";
// 	unsigned int	result1;
// 	unsigned int	result2;

// 	printf("Original strings:\n");
// 	printf("dst: %s\n", dst1);
// 	printf("src: %s\n", src);

// 	result1 = strlcat(dst1, src, sizeof(dst1));
// 	printf("\nStandard strlcat:\n");
// 	printf("Result: %s\n", dst1);
// 	printf("Return value: %u\n", result1);

// 	result2 = ft_strlcat(dst2, src, sizeof(dst2));
// 	printf("\nCustom ft_strlcat:\n");
// 	printf("Result: %s\n", dst2);
// 	printf("Return value: %u\n", result2);

// 	return (0);
// }
// cc -lbsd ft_strlcat.c