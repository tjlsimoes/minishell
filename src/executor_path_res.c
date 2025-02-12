/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:11:38 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_split(void)
{
	char	*path_value;
	char	**path_split;
	char	*temp;
	int		i;

	path_value = get_env_value(
			get_env_pair(&(get_sh()->env_var), "PATH"));
	if (!path_value)
		return (NULL);
	path_split = ft_split(path_value, ':');
	if (!path_split)
		return (free(path_value), NULL);
	i = 0;
	while (path_split[i])
	{
		temp = ft_strjoin(path_split[i], "/");
		if (!temp)
			break ;
		free(path_split[i]);
		path_split[i] = temp;
		i++;
	}
	free(path_value);
	return (path_split);
}
// Does not regard:
// Empty entries (::) or a trailing colon (:) in $PATH mean
// that Bash considers the current directory (.) as part of $PATH.
// Example: If $PATH=":/usr/bin", Bash searches . first.

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

void	attempt_path_resolution(t_ast_node **ast)
{
	t_ast_node	*node;
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