/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:38:30 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/30 17:13:09 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int wstatus)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (WIFEXITED(wstatus))
		minishell->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		minishell->exit_status = WTERMSIG(wstatus);
		if (minishell->exit_status != 131)
			minishell->exit_status += 128;
	}
}
// Not really sure why 131 ought to be handled differently...

// t_minishell	*get_minishell(void)
// {
// 	static t_minishell	minishell;

// 	return (&minishell);
// }

// void	do_something(void)
// {
// 	t_minishell	*minishell;
// 	int			wstatus;
// 	int			pid;

// 	minishell = get_minishell();
// 	minishell->exit_status = 42;

// 	pid = fork();
// 	if (pid == -1)
// 		exit(1);
// 	if (pid == 0)
// 	{
// 		printf("Hello from the child process!\n");
// 		// sleep(5);
// 		exit(0);
// 	}
// 	// sleep(1);
// 	// kill(pid, SIGINT);
// 	waitpid(pid, &wstatus, 0);

// 	set_exit_status(wstatus);
// 	printf("do_something: %d\n", minishell->exit_status);
// }

// int	main(void)
// {
// 	do_something();
// 	// printf("main: %d\n", get_minishell()->exit_status);
// 	printf("Hello\n");
// 	return (0);
// }