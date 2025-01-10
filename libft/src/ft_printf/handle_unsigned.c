/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:13 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/05 12:29:20 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_unsigned(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	return (ft_putnbr_base(num, "0123456789"));
}
