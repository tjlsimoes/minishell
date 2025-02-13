/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/13 11:40:23 by tjorge-l         ###   ########.fr       */
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

int	gen_redirect_out(t_ast_node **ast)
{
	char	*redirect_out;
	int		fd_out;

	redirect_out = get_redirect_out(ast);
	fd_out = -2;
	if (!redirect_out)
		return (1);
	fd_out = open(redirect_out , O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_out == -1)
		return (ft_putstr_fd("Open error\n", 2), 0); // Possible error message needed: errno.
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Dup2 error\n", 2), 0); // Possible error message needed: errno.
	if (close(fd_out) == -1)
		return (ft_putstr_fd("Close error\n", 2), 0); // Possible error message needed: errno.
	return (1);
}

int	gen_redirect_in(t_ast_node **ast)
{
	char	*redirect_in;
	int		fd_in;

	redirect_in = get_redirect_in(ast);
	fd_in = -2;
	if (!redirect_in)
		return (1);
	fd_in = open(redirect_in, O_RDONLY);
	if (fd_in == -1)
		return (0); // Possible error message needed: errno.
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (0); // Possible error message needed: errno.
	if (close(fd_in) == -1)
		return (0); // Possible error message needed: errno.
	return (1);
}

int	gen_append(t_ast_node **ast)
{
	char	*append;
	int		fd_out;

	append = get_append(ast);
	fd_out = -2;
	if (!append)
		return (1);
	fd_out = open(append, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_out == -1)
		return (ft_putstr_fd("Open error\n", 2), 0); // Possible error message needed: errno.
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Dup2 error\n", 2), 0); // Possible error message needed: errno.
	if (close(fd_out) == -1)
		return (ft_putstr_fd("Close error\n", 2), 0); // Possible error message needed: errno.
	return (1);
}

void	child_exec(char *abs_path, t_ast_node **ast)
{
	if (!gen_redirect_out(ast))
		return (free(abs_path), exit(1));
	if (!gen_redirect_in(ast))
		return (free(abs_path), exit(1));
	if (!gen_append(ast))
		return (free(abs_path), exit(1));
	if (execve(abs_path, generate_argv(ast), generate_envp()) == -1)
	{
		free(abs_path);
		exit(1); // More than possibly need to be able to free everyting
				 //   from here...
	}
	exit(0);
}
// Isn't there a need to free all the structs that are allocated in the
// parent process and "mirrored" in the child process?
// Even if execve doesn't fail?

// Is there a need to restore stdout and stdin if an error occurs?

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
		return (child_exec(abs_path, ast));
	waitpid(pid, &wstatus, 0);
	free(abs_path);
	set_exit_status(wstatus);
}

