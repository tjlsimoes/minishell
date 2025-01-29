/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:04 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/29 13:34:54 by asafrono         ###   ########.fr       */
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
static void	process_tokens(char *input)
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

int	main(void)
{
	char	*input;

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
	return (0);
}
