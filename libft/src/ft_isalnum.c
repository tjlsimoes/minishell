/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:10:00 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
	{
		return (8);
	}
	return (0);
}

// int	main(void)
// {
// 	char	test_chars[] = {'A', 'z', '0', '9', '@', ' ', '\n', '5'};
// 	int		array_size;
// 	int		i;
// 	int		original_result;
// 	int		custom_result;

// 	array_size = sizeof(test_chars) / sizeof(test_chars[0]);
// 	i = 0;
// 	while (i < array_size)
// 	{
// 		original_result = isalnum((unsigned char)test_chars[i]);
// 		custom_result = ft_isalnum(test_chars[i]);
// 		printf("Char: '%c' | Original: %d | Custom: %d\n",
// 			test_chars[i], original_result, custom_result);
// 		i++;
// 	}
// 	return (0);
// }
