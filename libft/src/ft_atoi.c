/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:00:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:10:01 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

// int	main(void)
// {
// 	char	*test1 = "  -123abc";
// 	char	*test2 = "   +456";
// 	char	*test3 = "  ---+--+1234ab567";
// 	char	*test4 = "  \t\n  789";
// 	char	*test5 = "0";
// 	printf("Test 1: ft_atoi: %d, atoi: %d\n", ft_atoi(test1), atoi(test1));
// 	printf("Test 2: ft_atoi: %d, atoi: %d\n", ft_atoi(test2), atoi(test2));
// 	printf("Test 3: ft_atoi: %d, atoi: %d\n", ft_atoi(test3), atoi(test3));
// 	printf("Test 4: ft_atoi: %d, atoi: %d\n", ft_atoi(test4), atoi(test4));
// 	printf("Test 5: ft_atoi: %d, atoi: %d\n", ft_atoi(test5), atoi(test5));
// 	return (0);
// }
