/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/05 15:53:01 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < size)
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	int			search_chars[] = {'o', 'W', '!', 'x', '\0'};
// 	int			len;
// 	int			i;
// 	void		*result1;
// 	void		*result2;

// 	len = strlen(str);
// 	i = 0;
// 	while (i < (int)(sizeof(search_chars) / sizeof(search_chars[0])))
// 	{
// 		printf("Searching for '%c' in \"%s\":\n", search_chars[i], str);
// 		result1 = memchr(str, search_chars[i], len);
// 		result2 = ft_memchr(str, search_chars[i], len);
// 		printf("Original memchr: ");
// 		if (result1 != NULL)
// 			printf("Found at position %d\n", (int)((char *)result1 - str));
// 		else
// 			printf("Not found\n");
// 		printf("Custom ft_memchr: ");
// 		if (result2 != NULL)
// 			printf("Found at position %d\n", (int)((char *)result2 - str));
// 		else
// 			printf("Not found\n");
// 		printf("\n");
// 		i++;
// 	}
// 	return (0);
// }
