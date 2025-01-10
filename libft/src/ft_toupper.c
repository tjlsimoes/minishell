/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:35 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// int	main(void)
// {
// 	char test_chars[] = {'a', 'z', 'A', 'Z', '0', '9', '@', '[', '`', '{'};
// 	unsigned int		i;
// 	int					original_result;
// 	int					custom_result;

// 	i = 0;
// 	while (i < sizeof(test_chars))
// 	{
// 		original_result = toupper(test_chars[i]);
// 		custom_result = ft_toupper(test_chars[i]);
// 		printf("Character: '%c' | Original: '%c' | Custom: '%c'\n",
// 			test_chars[i], original_result, custom_result);
// 		i++;
// 	}
// 	return (0);
// }
