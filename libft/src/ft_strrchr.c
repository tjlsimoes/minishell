/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:37 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
// #include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last);
}

// int	main(void)
// {
// 	const char	*str = "Hello, World! Hello, 42!";
// 	int			test_chars[] = {'l', 'o', '4', '!', 'x', '\0'};
// 	unsigned int			i;
// 	char		*result1;
// 	char		*result2;

// 	i = 0;
// 	while (i < sizeof(test_chars) / sizeof(test_chars[0]))
// 	{
// 		result1 = strrchr(str, test_chars[i]);
// 		result2 = ft_strrchr(str, test_chars[i]);
// 		printf("Searching for '%c':\n", test_chars[i]);
// 		printf("Original strrchr: ");
// 		if (result1 != NULL)
// 			printf("%s\n", result1);
// 		else
// 			printf("NULL\n");
// 		printf("Custom ft_strrchr: ");
// 		if (result2 != NULL)
// 			printf("%s\n", result2);
// 		else
// 			printf("NULL\n");
// 		printf("\n");
// 		i++;
// 	}
// 	return (0);
// }