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

	if (get_sigfree()->child)
	{
		sigfree_erase();
		child_free(NULL);
		exit(1); // Need to define exit?
	}
	printf("HERE Parent\n");
	// dup2(get_sigfree()->orig[0], STDIN_FILENO);
	// dup2(get_sigfree()->orig[1], STDOUT_FILENO);
	// sigfree_erase();

	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_sh()->should_exit = true;
}

void	setup_child_signals(void)
{
	struct sigaction	sigquit;
	struct sigaction	sigint;

	sigquit.sa_handler = handle_child_sig;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	sigaction(SIGQUIT, &sigquit, NULL);


	sigint.sa_handler = handle_child_sig;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
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

t_signal_free	*get_sigfree()
{
	static t_signal_free	sig_free;

	return (&sig_free);
}

void	sigfree_init(char *abs_path, bool child)
{
	t_signal_free	*sig_free;

	sig_free = get_sigfree();
	sig_free->abs_path = abs_path;
	sig_free->red[0] = -1;
	sig_free->red[1] = -1;
	sig_free->orig[0] = -1;
	sig_free->orig[1] = -1;
	sig_free->child = child;
}

void	sigfree_erase(void)
{
	t_signal_free	*sig_free;

	sig_free = get_sigfree();
	if (sig_free->abs_path)
	{
		free(sig_free->abs_path);
		sig_free->abs_path = NULL;
	}
	if (sig_free->red[1] >= 0)
		close(sig_free->red[1]);
	if (sig_free->red[0] >= 0)
		close(sig_free->red[0]);
	if (sig_free->orig[0] >= 0)
		close(sig_free->orig[0]);
	if (sig_free->orig[1] >= 0)
		close(sig_free->orig[1]);
}
