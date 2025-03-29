/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:09:17 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/27 11:45:27 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_sig(int sig)
{
	(void)sig;
	get_sigfree()->interrupted = 1;
	if (get_sigfree()->child)
	{
		sigfree_erase();
		// Possible need to free abs_path, argv, envp?
		// child_free(NULL); On child process this will already have been called.
		exit(sig);
	}
	close(STDIN_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	handle_heredoc_sig(int sig)
{
	(void)sig;
	get_sigfree()->interrupted = 1;
	def_exit(130);
	if (get_sigfree()->child)
	{
		sigfree_erase();
		child_free(NULL);
		exit(sig);
	}
	close(STDIN_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

t_signal_free	*get_sigfree(void)
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
	sig_free->interrupted = 0;
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
