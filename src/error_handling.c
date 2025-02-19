/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:38:17 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/19 18:04:20 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	report_error(t_error error_type, char *details)
{
	ft_putstr_fd("minishell: ", 2);
	if (error_type == ERROR_UNCLOSED_QUOTE)
		ft_putstr_fd("sytax error: unclosed quote", 2);
	else if (error_type == ERROR_SYNTAX)
		ft_putstr_fd("syntax error near unexpected token", 2);
	else if (error_type == ERROR_EXIT_TOO_MANY_ARGS)
		ft_putstr_fd("exit: too many arguments", 2);
	else if (error_type == ERROR_EXIT_NUMERIC_REQUIRED)
		ft_putstr_fd("exit: numeric argument required", 2);	
	else
		ft_putstr_fd("unknown error", 2);
	if (details)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(details, 2);
	}
	ft_putstr_fd("\n", 2);
}
