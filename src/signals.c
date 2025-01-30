/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:09:17 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/30 17:48:34 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

// Signal handler for SIGINT (Ctrl+C)
// Instead of directly writing to STDOUT, we should use 
// readline functions to handle the prompt properly.
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_status = 1;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

// no need to built it
// For the shell itself, you want to ignore SIGQUIT 
// (Ctrl+$$. This is achieved by using signal(SIGQUIT, SIG_IGN);
// in the setup_signals function. SIG_IGN is a special signal handler that
// tells the system to ignore the signal entirely.
// When you ignore a signal using SIG_IGN, you don't need to provide a 
// handler function. The system will automatically discard the signal 
// when it's received.
// Signal handler for SIGQUIT (Ctrl+\)
// void	handle_sigquit(int sig) {
// 	(void)sig;
// 	// Do nothing
// }

// int main() {
//     char *input;

//     // Set up signal handling
//     struct sigaction sa_int, sa_quit;

//     // SIGINT (Ctrl+C)
//     sa_int.sa_handler = handle_sigint;
//     sigemptyset(&sa_int.sa_mask);
//     sa_int.sa_flags = SA_RESTART; // Restart interrupted syscalls
//     if (sigaction(SIGINT, &sa_int, NULL) == -1) {
//         perror("sigaction(SIGINT)");
//         exit(EXIT_FAILURE);
//     }

// 	// SIGQUIT (Ctrl+\) - Ignore the signal
//     sa_quit.sa_handler = SIG_IGN; // Ignore SIGQUIT
//     sigemptyset(&sa_quit.sa_mask);
//     sa_quit.sa_flags = 0;
//     if (sigaction(SIGQUIT, &sa_quit, NULL) == -1) {
//         perror("sigaction(SIGQUIT)");
//         exit(EXIT_FAILURE);
//     }
//     // Main loop
//     while (1) {
//         input = readline("minishell> ");
//         if (input == NULL) { // Handle Ctrl+D
//             printf("\nExiting minishell...\n");
//             break;
//         }
//         if (strncmp(input, "exit", 5) == 0
//			&& (input[4] == '\0' || input[4] == '\n')) {
//             printf("\nExiting minishell...\n");
// 			free(input);
//             break;
//         } else if (strncmp(input, "history", 7) == 0) {
//             display_history();
//         } else if (strlen(input) > 0) {
//             add_history(input);
//             process_tokens(input);
//         }
//         free(input);
//     }

//     return 0;
// }
