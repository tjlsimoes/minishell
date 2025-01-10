/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:44 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	const char			*str = "Hello, World!";
// 	int					test_chars[] = {'l', 'o', 'x', '\0'};
// 	unsigned long		i;
// 	char				*result1;
// 	char				*result2;

// 	i = 0;
// 	while (i < sizeof(test_chars) / sizeof(test_chars[0]))
// 	{
// 		result1 = strchr(str, test_chars[i]);
// 		result2 = ft_strchr(str, test_chars[i]);
// 		printf("Searching for '%c':\n", test_chars[i]);

// 		printf("Original strchr: ");
// 		if (result1 != NULL)
// 			printf("%s\n", result1);
// 		else
// 			printf("NULL\n");

// 		printf("Custom ft_strchr: ");
// 		if (result2 != NULL)
// 			printf("%s\n\n", result2);
// 		else
// 			printf("NULL\n\n");

// 		i++;
// 	}
// 	return (0);
// }