/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:04 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 16:36:53 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get the current history list and print it
void	display_history(void)
{
	HIST_ENTRY	**hist_list;
	int			i;

	hist_list = history_list();
	i = -1;
	if (hist_list)
		while (hist_list[++i])
			printf("%d %s\n", i + 1, hist_list[i]->line);
}

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

void	init_minishell(char **envp)
{
	t_list		*env_var;
	t_minishell	*minishell;

	env_var = NULL;
	if (!envp)
		return ;
	while (*envp)
	{
		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
		envp++;
	}
	minishell = get_minishell();
	minishell->env_var = env_var;
	minishell->exit_status = 42;
}

int	process_command(char *input)
{
	if (ft_strncmp(input, "exit", 5) == 0
		&& (input[4] == '\0' || input[4] == '\n'))
		return (printf("\nExiting minishell...\n"), 0);
	else if (ft_strncmp(input, "history", 7) == 0)
		display_history();
	else if (ft_strlen(input) > 0)
	{
		add_history(input);
		process_tokens(input);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		continue_shell;

	setup_signals();
	if (!argc && !argv && !envp)
		return (1);
	init_minishell(envp);
	continue_shell = 1;
	while (continue_shell)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("\nExiting minishell...\n");
			break ;
		}
		continue_shell = process_command(input);
		free(input);
	}
	ft_lstdel(&(get_minishell()->env_var));
	return (0);
}
