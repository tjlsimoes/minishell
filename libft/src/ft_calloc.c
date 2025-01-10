/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:10:00 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb > 0 && (size > ((size_t) - 1) / nmemb))
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	return (ft_memset(ptr, 0, nmemb * size));
}

// int	main(void)
// {
// 	int		*numbers1;
// 	int		*numbers2;
// 	int		nmemb = 5;
// 	int		size = sizeof(int);
// 	int		i;

// 	numbers1 = (int *)calloc(nmemb, size);
// 	numbers2 = (int *)ft_calloc(nmemb, size);

// 	printf("Using calloc:\n");
// 	i = 0;
// 	while (i < nmemb)
// 	{
// 		printf("numbers1[%d]: %d\n", i, numbers1[i]);
// 		i++;
// 	}

// 	printf("\nUsing ft_calloc:\n");
// 	i = 0;
// 	while (i < nmemb)
// 	{
// 		printf("numbers2[%d]: %d\n", i, numbers2[i]);
// 		i++;
// 	}

// 	free(numbers1);
// 	free(numbers2);

// 	return (0);
// }
