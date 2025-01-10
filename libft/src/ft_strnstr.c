/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:38 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <bsd/string.h>  
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < size)
	{
		j = 0;
		while (big[i + j] && little[j] && i + j < size
			&& big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	*largestring = "Foo Bar Baz";
// 	const char	*smallstring = "Bar";
// 	char		*ptr1;
// 	char		*ptr2;

// 	printf("Searching in larger string: \"%s\"\n", largestring);
// 	printf("Searching for smaller string: \"%s\"\n\n", smallstring);

// 	ptr1 = strnstr(largestring, smallstring, 7);
// 	ptr2 = ft_strnstr(largestring, smallstring, 7);
// 	printf("Standard strnstr result: %s\n", ptr1);
// 	printf("Custom ft_strnstr result: %s\n\n", ptr2);

// 	ptr1 = strnstr(largestring, "Baz", 10);
// 	ptr2 = ft_strnstr(largestring, "Baz", 10);
// 	printf("Searching for \"Baz\" in larger string:\n");
// 	printf("Standard strnstr result: %s\n", ptr1);
// 	printf("Custom ft_strnstr result: %s\n\n", ptr2);

// 	ptr1 = strnstr(largestring, "z", 11);
// 	ptr2 = ft_strnstr(largestring, "z", 11);
// 	printf("Searching for \"z\" in larger string:\n");
// 	printf("Standard strnstr result: %s\n", ptr1);
// 	printf("Custom ft_strnstr result: %s\n\n", ptr2);

// 	ptr1 = strnstr(largestring, "", 5);
// 	ptr2 = ft_strnstr(largestring, "", 5);
// 	printf("Searching for an empty string in larger string:\n");
// 	printf("Standard strnstr result: %s\n", ptr1);
// 	printf("Custom ft_strnstr result: %s\n", ptr2);

// 	return (0);
// }
// cc -lbsd -Wall -Wextra -Werror ft_strnstr.c
