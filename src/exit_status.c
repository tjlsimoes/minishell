/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:38:30 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 19:29:06 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If child_wait evaluates to true it will follow a set
//   of conditions towards updating the stored exit status.
// It will also update the "exit status environment variable".

void	set_exit_status(int wstatus, bool child_wait)
{
	t_minishell	*minishell;
	char		*env_exit_status;
	char		*temp;

	minishell = get_sh();
	if (child_wait)
	{
		if (WIFEXITED(wstatus))
			minishell->exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			minishell->exit_status = WTERMSIG(wstatus);
			if (minishell->exit_status == SIGINT)
				write(STDERR_FILENO, "\n", 1);
			else if (minishell->exit_status == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			if (minishell->exit_status != 131)
				minishell->exit_status += 128;
		}
		else if (WIFSTOPPED(wstatus))
			minishell->exit_status = 128 + WSTOPSIG(wstatus);
	}
	env_exit_status = ft_itoa(minishell->exit_status);
	temp = ft_strjoin("?=", env_exit_status);
	add_env_var(&(get_sh()->env_var), temp);
	free(env_exit_status);
	free(temp);
}
// Not really sure why 131 ought to be handled differently...

// t_minishell	*get_sh(void)
// {
// 	static t_minishell	minishell;

// 	return (&minishell);
// }

// void	do_something(void)
// {
// 	t_minishell	*minishell;
// 	int			wstatus;
// 	int			pid;

// 	minishell = get_sh();
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
// 	// printf("main: %d\n", get_sh()->exit_status);
// 	printf("Hello\n");
// 	return (0);
// }
