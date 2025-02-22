/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:24:38 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/22 13:04:27 by asafrono         ###   ########.fr       */
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

static void	exit_shell(int exit_code, int orig_stdin, int orig_stdout)
{
	builtins_close_fds(orig_stdin, orig_stdout);
	child_free(NULL);
	exit(exit_code);
}

static int	process_exit_arg(char *arg)
{
	int	exit_code;

	if (!is_valid_number(arg))
		return (report_error(ERROR_EXIT_NUMERIC_REQUIRED, NULL), 2);
	exit_code = ft_atoi(arg) % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (exit_code);
}

int	ft_exit_exec(t_minishell *shell, t_ast_node *args,
		int orig_stdin, int orig_stdout)
{
	int		exit_code;
	char	*cleaned_arg;

	if (!args)
		exit_shell(shell->exit_status, orig_stdin, orig_stdout);
	if (args->right)
		return (report_error(ERROR_EXIT_TOO_MANY_ARGS, NULL), 1);
	cleaned_arg = clean_arg(args->value);
	exit_code = process_exit_arg(cleaned_arg);
	free(cleaned_arg);
	exit_shell(exit_code, orig_stdin, orig_stdout);
	return (exit_code);
}
