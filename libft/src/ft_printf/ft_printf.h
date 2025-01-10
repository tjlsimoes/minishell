/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:29:39 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 13:55:57 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft.h"

typedef struct s_flags
{
	int	width;
	int	precision;
	int	zero;
	int	minus;
	int	plus;
	int	space;
	int	hash;
}	t_flags;

// Main part
int		ft_printf(const char *format, ...);
int		handle_char(va_list args);
int		handle_string(va_list args);
int		handle_pointer(va_list args);
int		handle_int(va_list args);
int		handle_unsigned(va_list args);
int		handle_percent(void);
int		handle_format(char specifier, va_list args);
int		ft_putnbr_base(unsigned long long n, char *base);
int		handle_hex_lower(va_list args);
int		handle_hex_upper(va_list args);

// Bonus part
int		handle_char_bonus(va_list args, t_flags *flags);
int		handle_string_bonus(va_list args, t_flags *flags);
int		handle_pointer_bonus(va_list args);
int		handle_int_bonus(va_list args, t_flags *flags);
int		handle_unsigned_bonus(va_list args, t_flags *flags);
int		handle_hex_lower_bonus(va_list args, t_flags *flags);
int		handle_hex_upper_bonus(va_list args, t_flags *flags);
int		handle_percent_bonus(t_flags *flags);
int		handle_format_bonus(char specifier, va_list args, t_flags *flags);
void	initialize_flags(t_flags *flags);
void	parse_flags(const char **format, t_flags *flags);
int		print_padding(int width, char pad_char);
char	*ft_utoa(unsigned int n);
char	*ft_utoa_base(unsigned long long n, int base, int uppercase);
int		ft_putstr(char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
