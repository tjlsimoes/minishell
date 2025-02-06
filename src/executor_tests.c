/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:44:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/06 12:08:04 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Tests for ft_cd()

// void	process_tokens(char *input)
// {
// 	char		**tokens;
// 	t_ASTNode	*ast;

// 	tokens = tokenize_input(input);
// 	if (tokens)
// 	{
// 		ast = parse(tokens);
// 		pretty_print_ast(ast, 0);
// 		// printf("Initial %s\n", get_env_pair(&(get_sh()->env_var), "PWD"));
// 		simple_command_exec(&ast);
// 		// printf("Final %s\n", get_env_pair(&(get_sh()->env_var), "PWD"));
// 		free_tokens(tokens);
// 		free_ast(ast);
// 	}
// }

// Tests for ft_unset()
// Test with env builtin
// void	process_tokens(char *input)
// {
// 	char		**tokens;
// 	t_ASTNode	*ast;

// 	tokens = tokenize_input(input);
// 	if (tokens)
// 	{
// 		ast = parse(tokens);
// 		pretty_print_ast(ast, 0);
// 		printf("Initial %s\n", get_env_pair(&(get_sh()->env_var), "USER"));
// 		printf("Initial %s\n", get_env_pair(&(get_sh()->env_var), "HOME"));
// 		simple_command_exec(&ast);
// 		printf("Final %s\n", get_env_pair(&(get_sh()->env_var), "USER"));
// 		printf("Final %s\n", get_env_pair(&(get_sh()->env_var), "HOME"));
// 		free_ast(ast);
// 	}
// }

// Tests on env_var_value_treat(char **str)
// int	main(int argc, char **argv, char **envp)
// {
// 	char *str;
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	str = ft_strdup(argv[1]);
// 	ft_printf("Initial |%s|\n", str);
// 	env_var_value_treat(&str);
// 	ft_printf("Final |%s|\n", str);
// 	free(str);
	
// 	return (0);
// }
// valgrind ./minishell 'NAME="HELLO"'
// valgrind ./minishell 'NAME=""'
// valgrind ./minishell 'NAME='HELLO''
// valgrind ./minishell 'NAME='
// valgrind ./minishell 'NAME'
// valgrind ./minishell 'NAME="HELLO "'
// valgrind ./minishell ''