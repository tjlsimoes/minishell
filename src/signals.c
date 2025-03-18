/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:09:17 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 21:01:49 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Signal handler for SIGINT (Ctrl+C)
// Instead of directly writing to STDOUT, we should use
// readline functions to handle the prompt properly.
void	handle_sigint(int sig)
{
	(void)sig;
	def_exit(130);
	if (rl_readline_state & RL_STATE_READCMD)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_child_sig(int sig)
{
	(void)sig;
	printf("HERE\n");
	get_sh()->should_exit = true;
	// child_free(NULL);
	// def_exit(1);
}

void	setup_child_signals(void)
{
	struct sigaction	sigquit;
	struct sigaction	sigint;

	sigquit.sa_handler = handle_child_sig;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sigquit, NULL);


	sigint.sa_handler = handle_child_sig;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigint, NULL);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
