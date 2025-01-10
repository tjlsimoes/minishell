/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:14:36 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/06 16:37:23 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(unsigned long long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long long)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long long n, int base, int uppercase)
{
	char	*digits;
	char	*str;
	int		len;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = get_len(n, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = digits[n % base];
		n /= base;
	}
	return (str);
}
