/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:33:21 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/27 17:59:20 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid_number(char *str)
{
	long long	num;
	int			sign;

	num = 0;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		num = num * 10 + (*str - '0');
		if ((sign == 1 && num > INT_MAX)
			|| (sign == -1 && num > -(long long)INT_MIN))
			return (0);
		str++;
	}
	return (1);
}
