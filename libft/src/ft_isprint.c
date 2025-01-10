/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:57 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}

// int	main(void)
// {
// 	int	test_chars[] = {31, 32, 65, 126, 127, 0};
// 	int	i;

// 	i = 0;
// 	while (test_chars[i] != 0)
// 	{
// 		printf("Testing character ASCII %d:\n", test_chars[i]);
// 		printf("isprint: %d\n", isprint(test_chars[i]));
// 		printf("ft_isprint: %d\n\n", ft_isprint(test_chars[i]));
// 		i++;
// 	}
// 	return (0);
// }
