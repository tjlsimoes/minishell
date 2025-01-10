/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:40:58 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 13:05:18 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_hex_lower(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	return (ft_putnbr_base(num, "0123456789abcdef"));
}
