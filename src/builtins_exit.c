/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:24:38 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/22 11:42:55 by asafrono         ###   ########.fr       */
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

int	ft_exit_exec(t_minishell *shell, t_ast_node *args, bool in_child, int orig_stdin, int orig_stdout)
{
	int		exit_code;
	char    *cleaned_arg;

	if (!args)
	{
		if (!in_child)
		{
			builtins_close_fds(orig_stdin, orig_stdout);
			child_free(NULL);
			exit(shell->exit_status);
		}
		return (shell->exit_status);
	}
	if (args->right)
		return (report_error(ERROR_EXIT_TOO_MANY_ARGS, NULL), 1);
	cleaned_arg = clean_arg(args->value); 
	if (!is_valid_number(cleaned_arg))
	{
		report_error(ERROR_EXIT_NUMERIC_REQUIRED, NULL);
		exit_code = 2;
	}
	else
	{
		exit_code = ft_atoi(cleaned_arg);
		exit_code = exit_code % 256;
		if (exit_code < 0)
			exit_code += 256;
	}
	free(cleaned_arg);
	if (!in_child)
	{
		builtins_close_fds(orig_stdin, orig_stdout);
		child_free(NULL);
		exit(exit_code);
	}
	return (exit_code);
}
