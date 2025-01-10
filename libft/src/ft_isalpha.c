/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:46:17 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:59 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1024);
	}
	else
	{
		return (0);
	}
}

// int	main(void)
// {
// 	char	test_chars[] = {'A', 'z', '5', '@', 'M', 'p', '\n', ' ', '0'};
// 	int		array_size;
// 	int		i;
// 	int		original_result;
// 	int		custom_result;

// 	array_size = sizeof(test_chars) / sizeof(test_chars[0]);
// 	i = 0;
// 	while (i < array_size)
// 	{
// 		original_result = isalpha((unsigned char)test_chars[i]);
// 		custom_result = ft_isalpha(test_chars[i]);
// 		printf("Char: '%c' | Original: %d | Custom: %d\n",
// 			test_chars[i], original_result, custom_result);
// 		i++;
// 	}
// 	return (0);
// }
