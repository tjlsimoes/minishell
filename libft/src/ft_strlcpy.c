/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:01:35 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:40 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <bsd/string.h>  
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	src_len;
	unsigned int	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char			src[] = "Hello, World!";
// 	char			dst1[15];
// 	char			dst2[15];
// 	unsigned int	result1;
// 	unsigned int	result2;

// 	printf("Original string: %s\n", src);

// 	result1 = strlcpy(dst1, src, sizeof(dst1));
// 	printf("\nStandard strlcpy:\n");
// 	printf("Copied string: %s\n", dst1);
// 	printf("Return value: %u\n", result1);

// 	result2 = ft_strlcpy(dst2, src, sizeof(dst2));
// 	printf("\nCustom ft_strlcpy:\n");
// 	printf("Copied string: %s\n", dst2);
// 	printf("Return value: %u\n", result2);

// 	return (0);
// }
// cc -lbsd ft_strlcpy.c