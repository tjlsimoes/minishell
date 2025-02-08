/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:08:27 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/08 11:18:28 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**generate_argv(t_ASTNode **ast)
{
	int			size;
	char		**argv;
	t_ASTNode	*node;

	if (!ast || !(*ast) || !(*ast)->value)
		return (NULL);
	node = *ast;
	size = get_command_size(ast);
	argv = ft_calloc(1, ++size * sizeof(char *));
	if (!argv)
		return (NULL);
	size = 0;
	argv[size++] = ft_strdup(node->value);
	node = node->left;
	while (node)
	{
		argv[size++] = ft_strdup(node->value);
		if (!argv[size - 1])
			return (clear_array_idx(argv, size - 1), NULL);
		node = node->right;
	}
	argv[size] = NULL;
	return (argv);
}
// Note that there's no safeguard for size == 0
//   as that condition is safeguarded by the initial
//   conditional (if (!ast ...))

char	**generate_envp(void)
{
	char		**envp;
	int			size;
	t_list		*env_var;

	env_var = get_sh()->env_var;
	if (!env_var)
		return (NULL);
	size = ft_lstsize(env_var);
	if (size == 0)
		return (NULL);
	envp = (char **)ft_calloc(1, ++size * sizeof(char *));
	if (!envp)
		return (NULL);
	size = 0;
	while (env_var)
	{
		envp[size++] = ft_strdup(env_var->content);
		if (!envp[size - 1])
			return (clear_array_idx(envp, size - 1), NULL);
		env_var = env_var->next;
	}
	envp[size] = NULL;
	return (envp);
}
// Is there a need to safeguard possibility of
//   get_sh() returning NULL?

int	init_path_vars(char ***split, char *binary, int *i)
{
	if (!binary)
		return (1);
	*split = path_split();
	if (!split)
		return (path_error_env(binary), 1);
	*i = 0;
	return (0);
}

char	*path_resolution(char *binary)
{
	int		i;
	char	**split;
	char	*abs_path;

	if (init_path_vars(&split, binary, &i))
		return (NULL);
	while (split[i])
	{
		abs_path = ft_strjoin(split[i], binary);
		if (!abs_path)
			break ;
		if (access(abs_path, F_OK) == 0)
		{
			if (access(abs_path, X_OK) == 0)
				return (clear_array(split), abs_path);
			else
				return (path_error_x(&abs_path),
					clear_array(split), NULL);
		}
		free(abs_path);
		i++;
	}
	clear_array(split);
	path_error_f(binary);
	return (NULL);
}

void	attempt_path_resolution(t_ASTNode **ast)
{
	t_ASTNode	*node;
	char		*abs_path;
	int			pid;
	int			wstatus;

	node = *ast;
	abs_path = path_resolution(node->value);
	if (!abs_path)
		return ;
	pid = fork();
	if (pid == -1)
		return ;	// Possible error message needed.
	if (pid == 0)
		execve(abs_path, generate_argv(ast), generate_envp());
	waitpid(pid, &wstatus, 0);
	free(abs_path);
	set_exit_status(wstatus);
}
// Isn't it necessary to free result of generate_argv(ast)?
// And what about generate_envp()?

// Path Resolution
// Get $PATH's value
// Split PATH on ':'

// Traverse every element of PATH split
// searching for an executable matching
// the name of the command.
// Check if it exists.
// Check if it is executable.