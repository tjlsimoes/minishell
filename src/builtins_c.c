/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:33:32 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/31 12:34:42 by tjorge-l         ###   ########.fr       */
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

int	ft_echo(char *str, bool n)
{
	if (!str)
	{
		ft_printf("\n");
		return (0);
	}
	if (ft_printf("%s", str) != (int)ft_strlen(str))
		return (1);
	if (n)
	{
		if (ft_printf("\n") != (int)ft_strlen("\n"))
			return (1);
	}
	return (0);
}

// Has to run for more than one argument.
// e.g. echo "Hello" "World" => "Hello World"