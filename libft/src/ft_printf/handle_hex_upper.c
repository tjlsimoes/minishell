/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_upper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:01 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 17:59:10 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_hex_upper(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	return (ft_putnbr_base(num, "0123456789ABCDEF"));
}
