/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:30:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:58 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (2048);
	}
	return (0);
}

// int	main(void)
// {
// 	char	test_chars[] = {'0', '5', '9', 'A', 'z', '@', ' ', '\n'};
// 	int		array_size;
// 	int		i;
// 	int		original_result;
// 	int		custom_result;

// 	array_size = sizeof(test_chars) / sizeof(test_chars[0]);
// 	i = 0;
// 	while (i < array_size)
// 	{
// 		original_result = isdigit((unsigned char)test_chars[i]);
// 		custom_result = ft_isdigit(test_chars[i]);
// 		printf("Char: '%c' | Original: %d | Custom: %d\n",
// 			test_chars[i], original_result, custom_result);
// 		i++;
// 	}
// 	return (0);
// }
