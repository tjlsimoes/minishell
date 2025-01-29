/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:04 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/29 19:02:41 by tjorge-l         ###   ########.fr       */
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

//This function takes a user input string, tokenizes it into an array of
//tokens, constructs an abstract syntax tree (AST) from those tokens, 
//prints the AST structure, and then frees the allocated memory for tokens&AST.
void	process_tokens(char *input)
{
	char		**tokens;
	t_ASTNode	*ast;
	int			i;

	i = 0;
	tokens = tokenize_input(input);
	if (tokens)
	{
		ast = parse(tokens);
		pretty_print_ast(ast, 0);
		while (tokens[i] != NULL)
			free(tokens[i++]);
		free(tokens);
		free_ast(ast);
	}
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

int	main(int argc, char **argv, char **envp)
{
	char		*input;

	if (!argc && !argv && !envp)
		return (1);
	init_minishell(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL || (ft_strncmp(input, "exit", 5) == 0
				&& (input[4] == '\0' || input[4] == '\n')))
		{
			printf("\nExiting minishell...\n");
			break ;
		}
		else if (ft_strncmp(input, "history", 7) == 0)
			display_history();
		else if (ft_strlen(input) > 0)
		{
			add_history(input);
			process_tokens(input);
		}
		free(input);
	}
	ft_lstdel(&(get_minishell()->env_var));
	return (0);
}
