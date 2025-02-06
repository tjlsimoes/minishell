/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:50:23 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/30 17:13:36 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Passing the whole of the original shell's environment
// to a linked list.
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	del_env_var(&env_var, "NEW");
// 	print_env_vars(&env_var);
// 	ft_lstdel(&env_var);
// 	return (0);
// }


/////////////////////////////////////////////////////////////////
// Test strs_join(char **array)
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**output;
// 	char	*output_joined;
// 	int	i;
// 	t_list	*env_var;


// 	if (!argc && !argv && !envp)
// 		return (1);
// 	env_var = NULL;
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");

// 	output = env_vars_expansion("$HELLO!@#WVD@ $ZDRAVO $NEW $PATH $? $$$", &env_var);
// 	i = 0;
// 	while (output[i])
// 	{
// 		printf("env_vars_expansion[%d]: |%s|\n", i, output[i]);
// 		i++;
// 	}
// 	output_joined = strs_join(output);
// 	printf("Output joined: %s\n", output_joined);


// 	i = 0;
// 	while (output[i])
// 	{
// 		// printf("|%s|\n", output[i]);
// 		free(output[i++]);
// 	}
// 	ft_lstdel(&env_var);
// 	free(output_joined);
// 	free(output);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test env_vars_expansion(char *str): failed alloc mid-function
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**output;
// 	int		i;
// 	t_list	*env_var;


// 	if (!argc && !argv && !envp)
// 		return (1);
// 	env_var = NULL;
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");

// 	output = env_vars_expansion("$HELLO!@#WVD@ $ZDRAVO $NEW $PATH $? $$$", &env_var);
// 	if (!output)
// 	{
// 		ft_lstdel(&env_var);
// 		return (printf("Failed allocation.\n"), 1);
// 	}
// 	i = 0;
// 	while (output[i])
// 	{
// 		printf("|%s|\n", output[i]);
// 		free(output[i++]);
// 	}
// 	free(output);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test env_vars_expansion(char *str)
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**output;
// 	int	i;
// 	t_list	*env_var;


// 	if (!argc && !argv && !envp)
// 		return (1);
// 	env_var = NULL;
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");

// 	output = env_vars_expansion("$HELLO!@#WVD@ $Hello $PATH $? $$$", &env_var);
// 	ft_lstdel(&env_var);
// 	i = 0;
// 	while (output[i])
// 	{
// 		printf("|%s|\n", output[i]);
// 		free(output[i++]);
// 	}
// 	free(output);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test get_env_pair()
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;
// 	char	*output;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	// del_env_var(&env_var, "NEW");
// 	output = get_env_pair(&env_var, "ZDRAVO");
// 	output = get_env_pair(&env_var, "NEW");
// 	output = get_env_value(output);
// 	printf("Output: %s.\n", output);
// 	free(output);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test get_env_pair()
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;
// 	char	*output;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	// del_env_var(&env_var, "NEW");
// 	output = get_env_pair(&env_var, "ZDRAVO");
// 	output = get_env_pair(&env_var, "NEW");
// 	output = get_env_value(output);
// 	printf("Output: %s.\n", output);
// 	free(output);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test get_env_value()
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;
// 	char	*str;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	del_env_var(&env_var, "NEW");
// 	ft_lstdel(&env_var);
// 	str = get_env_value("ZDRAVO=ciao");
// 	printf("Pair: %s; Value: %s.\n", "ZDRAVO=ciao", str);
// 	free(str);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Update existing environment variable case.
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return (1);
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_var, ft_lstnew(ft_strdup(*envp)));
// 		envp++;
// 	}
// 	add_env_var(&env_var, "NEW=hello");
// 	add_env_var(&env_var, "NEW=hi");
// 	add_env_var(&env_var, "NEW=zdravo");
// 	add_env_var(&env_var, "OLDPWD=/");
// 	print_env_vars(&env_var);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// End of the list case
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return(1);
// 	ft_lstadd_back(&env_var, ft_lstnew(ft_strdup("NEW=hello")));
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	del_env_var(&env_var, "ZDRAVO");
// 	print_env_vars(&env_var);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Top of the list case
// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*env_var;

// 	env_var = NULL;
// 	if (!argc && !argv && !envp)
// 		return(1);
// 	ft_lstadd_back(&env_var, ft_lstnew(ft_strdup("NEW=hello")));
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	del_env_var(&env_var, "NEW");
// 	print_env_vars(&env_var);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Tests on expand_env_var()
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;

// 	if (!argc && !argv[1] && !envp)
// 		return(1);
// 	init_minishell(envp);
// 	str = ft_strdup(argv[1]);
// 	expand_env_var(&str);
// 	printf("Expanded: |%s|\n", str);
// 	free(str);
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }
// valgrind ./minishell '$YELLOW!Azkaban'
// ./minishell Hello$HOME!Azkaban
// ./minishell Hello$HOME

// valgrind ./minishell 'Hello$HOME!Azkaban'
// valgrind ./minishell '$HOME!Azkaban'
// valgrind ./minishell 'Hello$HOME!'

// valgrind ./minishell 'Hello$USER$HOME'
// valgrind ./minishell '$USER~lknsad$HOME'
// valgrind ./minishell '$USER$HOME~askdad'
// valgrind ./minishell 'asduhasdo$USER$HOME~askdad'
// valgrind ./minishell Hello$HOME\ $USER\ $USER\ $HOME\ $$$$$
// valgrind ./minishell 'Hello$HOME $USER $USER $$HOME $?'
// valgrind ./minishell 'Hello$HOME $USER $USER $$$HOME $?'