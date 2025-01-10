/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:08 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 13:40:04 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_pointer(va_list args)
{
	void	*ptr;
	int		count;

	ptr = va_arg(args, void *);
	count = 0;
	if (ptr == NULL)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	count += ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
	return (count);
}
