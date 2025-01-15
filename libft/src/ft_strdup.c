/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:48:12 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/15 15:41:07 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		length;
	int		i;

	if (!src)
		return (NULL);
	length = 0;
	i = 0;
	while (src[length])
		length++;
	dup = (char *)malloc(length + 1);
	if (dup == NULL)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int	main(void)
// {
// 	char *test1 = "Hello, World!";
// 	char *test2 = "42 School";
// 	char *dup1;
// 	char *dup2;

// 	dup1 = strdup(test1);
// 	dup2 = ft_strdup(test1);

// 	printf("Original: %s\n", test1);
// 	printf("Using strdup: %s\n", dup1);
// 	printf("Using ft_strdup: %s\n", dup2);

// 	free(dup1);
// 	free(dup2);

// 	dup1 = strdup(test2);
// 	dup2 = ft_strdup(test2);

// 	printf("\nOriginal: %s\n", test2);
// 	printf("Using strdup: %s\n", dup1);
// 	printf("Using ft_strdup: %s\n", dup2);

// 	free(dup1);
// 	free(dup2);

// 	return (0);
// }
