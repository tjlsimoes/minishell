/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:04 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/05 16:07:37 by tjorge-l         ###   ########.fr       */
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

t_minishell	*get_sh(void)
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
	minishell = get_sh();
	minishell->env_var = env_var;
	minishell->exit_status = 0;
}

int	process_command(char *input)
{
	t_minishell	*minishell;
	char		*status_str;
	
	minishell = get_minishell();
	if (ft_strncmp(input, "exit", 5) == 0
		&& (input[4] == '\0' || input[4] == '\n'))
		return (printf("\nExiting minishell...\n"), 0);
	else if (ft_strncmp(input, "history", 7) == 0)
		display_history();
	else if (ft_strncmp(input, "setstatus", 9) == 0)
	{
		status_str = input + 10;
		minishell->exit_status = ft_atoi(status_str);
		printf("Exit status set to: %d\n", minishell->exit_status);
	}
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
	ft_lstdel(&(get_sh()->env_var));
	return (0);
}
