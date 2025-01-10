/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:38:31 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:36 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
// int	main(void)
// {
// 	char	*str;
// 	char	*substr;

// 	str = "Hello, World!";
// 	printf("Original string: %s\n", str);

// 	substr = ft_substr(str, 7, 5);
// 	printf("Substring (start: 7, len: 5): %s\n", substr);
// 	free(substr);

// 	substr = ft_substr(str, 0, 5);
// 	printf("Substring (start: 0, len: 5): %s\n", substr);
// 	free(substr);

// 	substr = ft_substr(str, 13, 5);
// 	printf("Substring (start > strlen): %s\n", substr);
// 	free(substr);

// 	substr = ft_substr(str, 7, 100);
// 	printf("Substring (len > remaining): %s\n", substr);
// 	free(substr);

// 	substr = ft_substr(NULL, 0, 5);
// 	printf("Substring (NULL input): %s\n", substr);
// 	free(substr);

// 	return (0);
// }