/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:54:18 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/08 13:05:24 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	process_format(va_list args, const char *format)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (count);
			count += handle_format(*format, args);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = process_format(args, format);
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	// Test cases
// 	int count_printf;
// 	int count_ft_printf;

// 	// Test 1: Simple strings
// 	printf("Test 1: Simple strings\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Hello, World!\n");
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Hello, World!\n");
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 2: Characters
// 	char c = 'A';
// 	printf("Test 2: Single character\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Character: %c\n", c);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Character: %c\n", c);
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 3: Strings with NULL
// 	char *null_str = NULL;
// 	printf("Test 3: String with NULL pointer\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("String: %s\n", null_str);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("String: %s\n", null_str);
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 4: Integers
// 	int num = -12345;
// 	printf("Test 4: Negative integer\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Integer: %d\n", num);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Integer: %d\n", num);
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 5: Unsigned integers
// 	unsigned int u_num = 12345;
// 	printf("Test 5: Unsigned integer\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Unsigned Integer: %u\n", u_num);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Unsigned Integer: %u\n", u_num);
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 6: Hexadecimal (lowercase)
// 	unsigned int hex_num = 255;
// 	printf("Test 6: Hexadecimal (lowercase)\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Hexadecimal (lowercase): %x\n", hex_num);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Hexadecimal (lowercase): %x\n", hex_num);
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 7: Hexadecimal (uppercase)
// 	printf("Test 7: Hexadecimal (uppercase)\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Hexadecimal (uppercase): %X\n", hex_num);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Hexadecimal (uppercase): %X\n", hex_num);
// 	printf("Characters printed: %d\n\n", count_ft_printf);

// 	// Test 8: Pointer
// 	int a = 42;
// 	int *ptr = &a;
// 	printf("Test 8: Pointer address\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Pointer address: %p\n", (void *)ptr);
// 	printf("Characters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Pointer address: %p\n", (void *)ptr);
// 	printf("Characters printed: %d\n\n", count_ft_printf); 

// 	// Test 9: Percent sign
// 	printf("Test 9: Percent sign output\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf("Percent sign: %%\n");
// 	printf("\nCharacters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf("Percent sign: %%\n"); 
// 	printf("\nCharacters printed: %d\n\n", count_ft_printf); 

// 	// New Test: Null pointers
// 	printf("Test 10: Null pointers\n");
// 	printf("Standard printf:\n");
// 	count_printf = printf(" %p %p ", NULL, NULL);
// 	printf("\nCharacters printed: %d\n\n", count_printf);

// 	printf("Custom ft_printf:\n");
// 	count_ft_printf = ft_printf(" %p %p ", NULL, NULL);
// 	printf("\nCharacters printed: %d\n\n", count_ft_printf);

// 	return (0);
// }