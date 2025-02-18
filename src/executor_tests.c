/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:44:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/11 15:13:07 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Tests for ft_cd()

// void	process_tokens(char *input)
// {
// 	char		**tokens;
// 	t_ast_node	*ast;

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
// 	t_ast_node	*ast;

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


// Tests on path_resolution(char *binary)
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;
// 	char	*output;

// 	if (!argc && !argv[1] && !envp)
// 		return (1);
// 	init_minishell(envp);
// 	str = ft_strdup(argv[1]);
// 	output = path_resolution(argv[1]);
// 	printf("Output: |%s|\n", output);
// 	free(output);
// 	free(str);
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }
// valgrind --leak-check=full --track-origins=yes -s ./minishell 'mock'
// valgrind --leak-check=full --track-origins=yes -s ./minishell 'askjdada'
// valgrind --leak-check=full --track-origins=yes -s ./minishell 'echo'
// valgrind --leak-check=full --track-origins=yes -s ./minishell 'ls'
// valgrind --leak-check=full --track-origins=yes -s ./minishell 'grep'

///////////////////////////////////////////////////////////////////////////
// Tests on generate_argv()
// void	print_array(char **array)
// {
// 	int	i;

// 	if (!array || !(*array))
// 		return ;
// 	i = 0;
// 	while (array[i])
// 	{
// 		ft_printf("%s\n", array[i]);
// 		i++;
// 	}
// }

// void	process_tokens(char *input)
// {
// 	char		**tokens;
// 	char		**argv;
// 	t_ast_node	*ast;

// 	tokens = tokenize_input(input);
// 	if (tokens)
// 	{
// 		ast = parse(tokens);
// 		pretty_print_ast(ast, 0);
// 		// simple_command_exec(&ast);
// 		argv = generate_argv(&ast);
// 		print_array(argv);
// 		clear_array(argv);
// 		free_tokens(tokens);
// 		free_ast(ast);
// 	}
// }


///////////////////////////////////////////////////////////////////////////
// Tests on generate_envp()

// Test generate_envp(): from within minishell
// void	print_array(char **array)
// {
// 	int	i;

// 	if (!array || !(*array))
// 		return ;
// 	i = 0;
// 	while (array[i])
// 	{
// 		ft_printf("%s\n", array[i]);
// 		i++;
// 	}
// }

// void	process_tokens(char *input)
// {
// 	char		**tokens;
// 	char		**envp;
// 	t_ast_node	*ast;

// 	tokens = tokenize_input(input);
// 	if (tokens)
// 	{
// 		ast = parse(tokens);
// 		pretty_print_ast(ast, 0);
// 		// simple_command_exec(&ast);
// 		envp = generate_envp(&ast);
// 		print_array(envp);
// 		clear_array(envp);
// 		free_tokens(tokens);
// 		free_ast(ast);
// 	}
// }

///////////////////////////////////////////////////////////////////////////
// Test generate_envp(): whole valid original envp
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**new_envp;

// 	if (!argc && !argv && !envp)
// 		return (1);
// 	init_minishell(envp);
// 	new_envp = generate_envp();
// 	print_array(new_envp);
// 	clear_array(new_envp);
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }

///////////////////////////////////////////////////////////////////////////
// Test generate_envp(): inexistant original envp
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**new_envp;

// 	if (!argc && !argv && !envp)
// 		return (1);
// 	init_minishell(envp);
// 	ft_lstdel(&(get_sh()->env_var));
// 	// get_sh()->env_var = NULL;
// 	new_envp = generate_envp();
// 	print_array(new_envp);
// 	clear_array(new_envp);
// 	return (0);
// }

///////////////////////////////////////////////////////////////////////////
// Test any()
// int	main(int argc, char **argv)
// {
// 	char *builtins[7] = {"cd", "pwd", "echo", "env", "unset", "export", NULL};

// 	if (!argc || !argv)
// 		return (1);
// 	printf("any() output: %d\n", any(builtins, argv[1]));
// 	return (0);
// }

///////////////////////////////////////////////////////////////////////////
// Test rm_tab_trail(char **str)

// int	main(int argc, char **argv)
// {
// 	char	*str;
// 	if (!argc || !argv[1])
// 		return (1);
// 	str = ft_strdup(argv[1]);
// 	printf("Original string: |%s|\n", str);
// 	rm_tab_trail(&str);
// 	printf("Modified string: |%s|\n", str);
// 	free(str);
// 	return (0);
// }

///////////////////////////////////////////////////////////////////////////
// Test rm_tab_trail(char **str)

// int	main(int argc, char **argv)
// {
// 	char	*str;
// 	// char	temp[] = {'"', 'E', '"', 'O', 'F', '\0'};
// 	// char	temp[] = {'"', 'E', '"', '\'', 'O', '\'', 'F', '\0'};
// 	// char	temp[] = {'"', 'E', '"', '\'', 'O', '\'', '"', 'F', '"', '\0'};
// 	// char	temp[] = {'"', '"', '\0'};
// 	// char	temp[] = {'\'', '\'', '\0'};
// 	char	temp[] = {'\0'};

// 	if (!argc || !argv[1])
// 		return (1);
	
// 	str = ft_strdup(temp);
// 	// str = ft_strdup(argv[1]);
// 	printf("Original string: |%s|\n", str);
// 	alt_rm_quotes(&str);
// 	printf("Modified string: |%s|\n", str);
// 	free(str);
// 	return (0);
// }