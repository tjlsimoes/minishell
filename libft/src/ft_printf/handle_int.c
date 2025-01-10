/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:04 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 14:28:03 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_int(va_list args)
{
	int	num;

	num = va_arg(args, int);
	return (ft_putnbr(num));
}
