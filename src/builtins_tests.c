/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:40:33 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/31 12:40:44 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	main(int argc, char **argv, char **envp)
// {
// 	if (!argc || !argv)
// 		return (1);
// 	init_minishell(envp);
// 	ft_cd(argv[1]);
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }


/////////////////////////////////////////////////////////////////
//Test on ft_unset()
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*env_pair;
// 	char	*key;

// 	if (!argc || !argv)
// 		return (1);
// 	env_pair = ft_strdup(argv[1]);
// 	init_minishell(envp);
// 	if (ft_export(&env_pair))
// 	{
// 		ft_lstdel(&(get_sh()->env_var));
// 		free(env_pair);
// 		return (1);
// 	}
// 	key = get_env_key(env_pair);
// 	printf("%s\n", get_env_pair(&(get_sh()->env_var), key));
// 	ft_unset(key);
// 	if (!get_env_pair(&(get_sh()->env_var), key))
// 		printf("Deleted!\n");
// 	ft_lstdel(&(get_sh()->env_var));
// 	free(env_pair);
// 	free(key);
// 	return (0);
// }


/////////////////////////////////////////////////////////////////
//Test on ft_export()
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*env_pair;
// 	char	*key;

// 	if (!argc || !argv)
// 		return (1);
// 	env_pair = ft_strdup(argv[1]);
// 	init_minishell(envp);
// 	if (ft_export(&env_pair))
// 	{
// 		ft_lstdel(&(get_sh()->env_var));
// 		free(env_pair);
// 		return (1);
// 	}
// 	key = get_env_key(env_pair);
// 	printf("%s\n", get_env_pair(&(get_sh()->env_var), key));
// 	ft_lstdel(&(get_sh()->env_var));
// 	free(env_pair);
// 	free(key);
// 	return (0);
// }

// valgrind ./minishell 'NEW=HELLO'
// valgrind ./minishell 'NEW='
// valgrind ./minishell 'NEW'
// valgrind ./minishell '_NEW'
// valgrind ./minishell '_NEW='
// valgrind ./minishell '?NEW='
// valgrind ./minishell '-NEW='
// valgrind ./minishell '1NEW'
// valgrind ./minishell '1NEW'
// valgrind ./minishell '1NEW='
// valgrind ./minishell 'NEW =hello'
// valgrind ./minishell '*=hello'
// valgrind ./minishell '$*=hello'
// valgrind ./minishell '$?=hello'
// valgrind ./minishell '$@=hello'
// valgrind ./minishell '$#=hello'
// valgrind ./minishell '$-=hello'
// valgrind ./minishell '$!=hello'
// valgrind ./minishell '$0=hello'
// valgrind ./minishell '*=hello'
// valgrind ./minishell '@=hello'
// valgrind ./minishell '#=hello'
// valgrind ./minishell '?=hello'
// valgrind ./minishell '-=hello'
// valgrind ./minishell '$=hello'
// valgrind ./minishell '!=hello'
// valgrind ./minishell '0=hello'
// valgrind ./minishell 'HOME=nothome!'


/////////////////////////////////////////////////////////////////
//Test on print_env
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
// 	add_env_var(&env_var, "NEW=");
// 	add_env_var(&env_var, "ZDRAVO=ciao");
// 	print_env_vars(&env_var);
// 	ft_lstdel(&env_var);
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test on ft_pwd()
// int	main(void)
// {
// 	ft_pwd();
// 	return (0);
// }

/////////////////////////////////////////////////////////////////
// Test on ft_echo()
// int	main(int argc, char **argv)
// {
// 	if (!argc || !argv)
// 		return (1);
// 	ft_echo(argv[1], ft_atoi(argv[2]));
// 	return (0);
// }

// Test on ft_echo(): exit status
// int	main(int argc, char **argv)
// {
// 	if (!argc || !argv)
// 		return (1);
// 	printf("%d\n", ft_echo(argv[1], ft_atoi(argv[2])));
// 	return (0);
// }

// valgrind ./minishell 'hello' '1'
// valgrind ./minishell 'hello' '0'
// valgrind ./minishell 'hellaysgiaffaasufoasdao' '1'
// valgrind ./minishell 'hellaysgiaffaasufoasdao' '0'

/////////////////////////////////////////////////////////////////
// Tests for ft_cd()

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*path;
// 	if (!argc || !argv)
// 		return (1);
// 	path = ft_strdup(argv[1]);
// 	init_minishell(envp);
// 	ft_cd(&path);
// 	printf("%s\n", get_env_pair(&(get_sh()->env_var), "PWD"));
// 	printf("%s\n", get_env_pair(&(get_sh()->env_var), "OLDPWD"));
// 	ft_lstdel(&(get_sh()->env_var));
// 	free(path);
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	if (!argc || !argv)
// 		return (1);
// 	init_minishell(envp);
// 	add_env_var(&(get_sh()->env_var), "PWD=/");
// 	printf("%s\n", get_env_pair(&(get_sh()->env_var), "PWD"));
// 	ft_cd(argv[1]);
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	if (!argc || !argv)
// 		return (1);
// 	init_minishell(envp);
// 	ft_cd("/");
// 	ft_cd("..");
// 	ft_cd("..");
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	if (!argc || !argv)
// 		return (1);
// 	init_minishell(envp);
// 	mkdir("test_dir", S_IRWXU);
// 	ft_cd("test_dir/");
// 	rmdir("/home/pgr/repos/42/aleksandr/test_dir/");
// 	ft_cd("../..");
// 	ft_cd("-");
// 	ft_cd("/home/pgr/repos/42/aleksandr/");
// 	ft_lstdel(&(get_sh()->env_var));
// 	return (0);
// }