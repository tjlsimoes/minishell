/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:38:17 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/09 11:58:26 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_message_extended(t_error error_type)
{
	if (error_type == ERROR_DUP2)
		ft_putstr_fd("dup2 error", 2);
	else if (error_type == ERROR_PIPE)
		ft_putstr_fd("pipe error", 2);
	else if (error_type == ERROR_FORK)
		ft_putstr_fd("fork error", 2);
	else if (error_type == ERROR_OPEN)
		ft_putstr_fd("open error", 2);
	else if (error_type == ERROR_CLOSE)
		ft_putstr_fd("close error", 2);
	else if (error_type == ERROR_IS_DIR)
		ft_putstr_fd("is a directory", 2);
	else
		ft_putstr_fd("unknown error", 2);
}

static void	print_error_message(t_error error_type)
{
	if (error_type == ERROR_UNCLOSED_QUOTE)
		ft_putstr_fd("syntax error: unclosed quote", 2);
	else if (error_type == ERROR_SYNTAX)
		ft_putstr_fd("syntax error near unexpected token", 2);
	else if (error_type == ERROR_EXIT_TOO_MANY_ARGS)
		ft_putstr_fd("exit: too many arguments", 2);
	else if (error_type == ERROR_EXIT_NUMERIC_REQUIRED)
		ft_putstr_fd("exit: numeric argument required", 2);
	else if (error_type == ERROR_INVALID_IDENTIFIER)
		ft_putstr_fd("export: not a valid identifier", 2);
	else if (error_type == ERROR_ENV_WRITE_FAILED)
		ft_putstr_fd("env: write error", 2);
	else if (error_type == ERROR_CD_TOO_MANY_ARGS)
		ft_putstr_fd("cd: too many arguments", 2);
	else if (error_type == ERROR_COMMAND_NOT_FOUND)
		ft_putstr_fd("command not found", 2);
	else if (error_type == ERROR_PERMISSION_DENIED)
		ft_putstr_fd("Permission denied", 2);
	else if (error_type == ERROR_NO_SUCH_FILE_OR_DIR)
		ft_putstr_fd("No such file or directory", 2);
	else
		print_error_message_extended(error_type);
}

void	report_error(t_error error_type, char *details)
{
	ft_putstr_fd("minishell: ", 2);
	print_error_message(error_type);
	if (details)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(details, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	chdir_error(char **path)
{
	ft_putstr_fd("minihsell: cd: ", 2);
	ft_putstr_fd((*path), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	def_exit(int exit_nbr)
{
	get_sh()->exit_status = exit_nbr;
	set_exit_status(-1, false);
}
