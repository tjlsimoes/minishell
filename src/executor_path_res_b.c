/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res_b.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 21:14:55 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(char *abs_path, t_ast_node **ast)
{
	// signal(SIGINT, SIG_DFL);
	child_exec(abs_path, ast);
	exit_shell(1, -1, -1);
}

static void	handle_fork_error(char *abs_path)
{
	report_error(ERROR_FORK, "Failed to fork process");
	get_sh()->exit_status = 1;
	set_exit_status(get_sh()->exit_status, false);
	free(abs_path);
}

void	attempt_path_resolution(t_ast_node **ast)
{
	t_ast_node	*node;
	char		*abs_path;
	int			pid;
	int			wstatus;
	void		(*orig_sigint)(int);

	node = *ast;
	abs_path = path_resolution(node->value);
	if (!abs_path || cmd_check(abs_path))
		return ;
	sigfree_init(abs_path, true);
	orig_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(abs_path));
	if (pid == 0)
		handle_child_process(abs_path, ast);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, orig_sigint);
	free(abs_path);
	set_exit_status(wstatus, true);
}
