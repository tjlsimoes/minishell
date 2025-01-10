/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:44:23 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 14:26:21 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

// int main(void)
// {
//     // Test 1: Write to stdout (file descriptor 1)
//     write(1, "Writing 'A' to stdout: ", 23);
//     ft_putchar_fd('A', 1);
//     ft_putchar_fd('\n', 1);

//     // Test 2: Write to stderr (file descriptor 2)
//     write(2, "Writing 'B' to stderr: ", 23);
//     ft_putchar_fd('B', 2);
//     ft_putchar_fd('\n', 2);

//     // Test 3: Write multiple characters to stdout
//     write(1, "Writing 'Hello' to stdout: ", 27);
//     ft_putchar_fd('H', 1);
//     ft_putchar_fd('e', 1);
//     ft_putchar_fd('l', 1);
//     ft_putchar_fd('l', 1);
//     ft_putchar_fd('o', 1);
//     ft_putchar_fd('\n', 1);

//     // Test 4: Write a newline character
//     write(1, "Writing a newline character: ", 29);
//     ft_putchar_fd('\n', 1);

//     return 0;
// }
