/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/19 18:42:48 by asafrono         ###   ########.fr       */
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
		return (report_error(ERROR_NO_SUCH_FILE_OR_DIR, binary), 1);
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
				return (report_error(ERROR_PERMISSION_DENIED, abs_path),
					free(abs_path),clear_array(split), NULL);
		}
		free(abs_path);
		i++;
	}
	clear_array(split);
	report_error(ERROR_COMMAND_NOT_FOUND, binary);
	return (NULL);
}

void	child_exec(char *abs_path, t_ast_node **ast)
{
	char	**argv;
	char	**envp;

	if (!gen_heredoc(ast))
		return (child_free(abs_path), exit(0));
	if (!gen_redirect_in(ast))
		return (child_free(abs_path), exit(0));
	if (!gen_redirect_out(ast))
		return (child_free(abs_path), exit(0));
	if (!gen_append(ast))
		return (child_free(abs_path), exit(0));
	argv = generate_argv(ast);
	envp = generate_envp();
	// Shouldn't all memory aside from argv and envp not be freed?
	if (execve(abs_path, argv, envp) == -1)
	{
		child_free(abs_path);
		clear_array(argv);
		clear_array(envp);
		exit(0);
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
		return (free(abs_path));	// Possible error message needed.
	if (pid == 0)
		return (child_exec(abs_path, ast));
	waitpid(pid, &wstatus, 0);
	free(abs_path);
	set_exit_status(wstatus);
}
