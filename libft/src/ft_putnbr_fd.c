/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:45:49 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 14:37:14 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
#include "libft.h"

static void	ft_putnbr_recursive(long n, int fd)
{
	if (n > 9)
		ft_putnbr_recursive(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	else if (num == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n == -2147483648)
	{
		ft_putchar_fd('2', fd);
		num = 147483648;
	}
	ft_putnbr_recursive(num, fd);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar(n % 10 + '0');
	return (count);
}

// int main(void)
// {
//     // Test 1: Write positive number to stdout
//     write(1, "Test 1 - Positive number: ", 26);
//     ft_putnbr_fd(42, 1);
//     write(1, "\n", 1);

//     // Test 2: Write negative number to stdout
//     write(1, "Test 2 - Negative number: ", 26);
//     ft_putnbr_fd(-42, 1);
//     write(1, "\n", 1);

//     // Test 3: Write zero to stdout
//     write(1, "Test 3 - Zero: ", 15);
//     ft_putnbr_fd(0, 1);
//     write(1, "\n", 1);

//     // Test 4: Write largest possible int (INT_MAX)
//     write(1, "Test 4 - INT_MAX: ", 18);
//     ft_putnbr_fd(2147483647, 1);
//     write(1, "\n", 1);

//     // Test 5: Write INT_MIN to stdout
//     write(1, "Test 5 - INT_MIN: ", 18);
//     ft_putnbr_fd(-2147483648, 1);
//     write(1, "\n", 1);

//     // Test 6: Write to stderr
//     write(2, "Test 6 - Writing to stderr: ", 28);
//     ft_putnbr_fd(123, 2);
//     write(2, "\n", 1);

//     return (0);
// }