/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:40:55 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/04 18:01:39 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(char specifier, va_list args)
{
	if (specifier == 'c')
		return (handle_char(args));
	else if (specifier == 's')
		return (handle_string(args));
	else if (specifier == 'p')
		return (handle_pointer(args));
	else if (specifier == 'd' || specifier == 'i')
		return (handle_int(args));
	else if (specifier == 'u')
		return (handle_unsigned(args));
	else if (specifier == 'x')
		return (handle_hex_lower(args));
	else if (specifier == 'X')
		return (handle_hex_upper(args));
	else if (specifier == '%')
		return (handle_percent());
	return (0);
}
