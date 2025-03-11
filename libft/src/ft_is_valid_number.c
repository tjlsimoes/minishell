/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:33:21 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/19 17:51:25 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_non_digits(char *str, int *sign)
{
	while (ft_isspace(*str))
		str++;
	*sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	while (ft_isspace(*str) || *str == '"' || *str == '\'')
		str++;
	return (str);
}

int	is_valid_number(char *str)
{
	long long	num;
	int			sign;

	num = 0;
	str = skip_non_digits(str, &sign);
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			str++;
			continue ;
		}
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
