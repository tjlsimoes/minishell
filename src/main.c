/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:42:04 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/14 14:15:33 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		print_ast(ast, 0);
		while (tokens[i] != NULL)
			free(tokens[i++]);
		free(tokens);
		free_ast(ast);
	}
}

int	main(int argc, char **argv)
{
	char	*input;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL || (ft_strncmp(input, "exit", 5) == 0
				&& (input[4] == '\0' || input[4] == '\n')))
		{
			printf("\nExiting minishell...\n");
			break ;
		}
		if (ft_strlen(input) > 0)
			process_tokens(input);
		free(input);
	}
	return (0);
}
