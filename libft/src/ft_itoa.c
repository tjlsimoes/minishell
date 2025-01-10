/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:43:20 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 14:09:57 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

static int	ft_numlen(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static void	ft_putnbr_str(int n, char *str, int *i)
{
	if (n > 9)
		ft_putnbr_str(n / 10, str, i);
	str[(*i)++] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	len = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (n == -2147483648)
	{
		str[i++] = '-';
		str[i++] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		str[i++] = '-';
		n = -n;
	}
	ft_putnbr_str(n, str, &i);
	str[i] = '\0';
	return (str);
}

// int	main(void)
// {
// 	int		numbers[] = {0, -42, 42, 2147483647, -2147483648, 100, -100};
// 	int		count = sizeof(numbers) / sizeof(numbers[0]);
// 	char	*result;
// 	int		i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		result = ft_itoa(numbers[i]);
// 		if (result)
// 		{
// 			printf("Input: %d, Output: %s\n", numbers[i], result);
// 			free(result);
// 		}
// 		else
// 			printf("Memory allocation failed for %d\n", numbers[i]);
// 		i++;
// 	}
// 	return (0);
// }