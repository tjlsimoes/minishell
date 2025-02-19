/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:24:38 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/19 18:05:56 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*clean_arg(char *arg)
{
	char	*clean;
	char	*write;

	clean = ft_strdup(arg);
	write = clean;
	while (*arg)
	{
		if (*arg != '"' && *arg != '\'')
			*write++ = *arg;
		arg++;
	}
	*write = '\0';
	return (clean);
}

int	ft_exit_exec(t_minishell *shell, t_ast_node *args, bool in_child)
{
	int	exit_code;

	if (!args)
	{
		if (!in_child)
			exit(shell->exit_status);
		return (shell->exit_status);
	}
	if (args->right)
		return (report_error(ERROR_EXIT_TOO_MANY_ARGS, NULL), 1);
	if (!is_valid_number(clean_arg(args->value)))
	{
		report_error(ERROR_EXIT_NUMERIC_REQUIRED, NULL);
		exit_code = 2;
	}
	else
	{
		exit_code = ft_atoi(clean_arg(args->value));
		exit_code = exit_code % 256;
		if (exit_code < 0)
			exit_code += 256;
	}
	if (!in_child)
		exit(exit_code);
	return (exit_code);
}
