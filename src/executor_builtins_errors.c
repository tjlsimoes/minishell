/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtins_errors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:09:39 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:09:46 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_error_f(char *binary)
{
	ft_putstr_fd(binary, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	path_error_x(char **abs_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*abs_path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free(*abs_path);
}

void	path_error_env(char *binary)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(binary, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
