/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:33:32 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/06 19:00:09 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX);
	if (!(getcwd(cwd, PATH_MAX)))
	{
		perror("-bash: pwd");
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}

// n is taken as indicative of -n 
// being present, not that a newline
// ought to be printed.
int	ft_echo(char *str, bool n)
{
	if (!str)
	{
		if (!n)
		{
			if (ft_printf("\n") != (int)ft_strlen("\n"))
				return (1);
		}
		return (0);
	}
	if (ft_printf("%s", str) != (int)ft_strlen(str))
		return (1);
	if (!n)
	{
		if (ft_printf("\n") != (int)ft_strlen("\n"))
			return (1);
	}
	return (0);
}

// Has to run for more than one argument.
// e.g. echo "Hello" "World" => "Hello World"
// Do away with the overcomplication?
