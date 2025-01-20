/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:09:17 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/20 10:07:20 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Signal handler for SIGINT (Ctrl+C)
void	handle_sigint(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\nminishell> ", 12); // Print prompt on a new line
}

// Signal handler for SIGQUIT (Ctrl+\)
void	handle_sigquit(int sig) {
    (void)sig;
    // Do nothing
}

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
//         if (strncmp(input, "exit", 5) == 0 && (input[4] == '\0' || input[4] == '\n')) {
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
