/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:45:21 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/29 13:32:33 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	if (s)
		write(fd, s, ft_strlen(s));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		i += ft_putchar(str[i]);
	return (i);
}

// int main(void)
// {
//     // Test 1: Write to stdout (file descriptor 1)
//     write(1, "Test 1 - Writing to stdout: ", 28);
//     ft_putstr_fd("Hello, World!\n", 1);

//     // Test 2: Write to stderr (file descriptor 2)
//     write(2, "Test 2 - Writing to stderr: ", 28);
//     ft_putstr_fd("This is an error message.\n", 2);

//     // Test 3: Write an empty string
//     write(1, "Test 3 - Writing an empty string: ", 34);
//     ft_putstr_fd("", 1);
//     write(1, "(end of empty string)\n", 22);

//     // Test 4: Write a string with special characters
//     write(1, "Test 4 - String with special characters: ", 41);
//     ft_putstr_fd("Tab\tNewline\n", 1);
//     write(1, "(end of special characters)\n", 28);

//     // Test 5: Write a NULL string (should not write anything)
//     write(1, "Test 5 - Writing NULL string: ", 30);
//     ft_putstr_fd(NULL, 1);
//     write(1, "(end of NULL string test)\n", 26);

//     return (0);
// }
