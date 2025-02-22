/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:04 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/21 15:03:25 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	minishell->input = NULL;
	minishell->env_var = env_var;
	minishell->tokens = NULL;
	minishell->ast = NULL;
	minishell->exit_status = 0;
	ft_lstadd_back(&env_var, ft_lstnew(ft_strdup("?=0")));
}

int	process_command(char *input)
{
	t_minishell	*minishell;
	char		*status_str;

	minishell = get_sh();
	if (ft_strncmp(input, "setstatus", 9) == 0)
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
	int			continue_shell;
	t_minishell	*sh;

	setup_signals();
	if (!argc && !argv && !envp)
		return (1);
	init_minishell(envp);
	sh = get_sh();
	continue_shell = 1;
	while (continue_shell)
	{
		sh->input = readline("minishell> ");
		if (sh->input == NULL)
			break ;
		continue_shell = process_command(sh->input);
		free(sh->input);
	}
	ft_lstdel(&(sh->env_var));
	return (0);
}
// Is there a need to safeguard against:
// - Error initializing get_sh()->env_var?