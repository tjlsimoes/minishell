/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:12:41 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 12:58:21 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned long long n, char *base)
{
	int					count;
	unsigned long long	base_len;

	count = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (n >= base_len)
	{
		count += ft_putnbr_base(n / base_len, base);
		count += ft_putnbr_base(n % base_len, base);
	}
	else
	{
		ft_putchar_fd(base[n], 1);
		count++;
	}
	return (count);
}
