/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/23 14:33:30 by asafrono         ###   ########.fr       */
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
	path_split = get_path_split(path_value, ':');
	if (!path_split)
		return (free(path_value), NULL);
	i = 0;
	while (path_split[i])
	{
		temp = get_abs_path(path_split[i]);
		if (!temp)
			break ;
		free(path_split[i]);
		path_split[i] = temp;
		i++;
	}
	free(path_value);
	return (path_split);
}

char	*path_resolution(char *binary)
{
	char	**split;
	int		path_split_need;

	path_split_need = init_path_vars(&split, binary);
	if (!path_split_need)
		return (NULL);
	else if (path_split_need == 2)
		return (ft_strdup(binary));
	else if (path_split_need == 3)
		return (gen_path_pwd(binary));
	else if (path_split_need == 4)
		return (gen_path_rel(binary));
	return (path_res_iter(&split, binary));
}

void	child_exec(char *abs_path, t_ast_node **ast)
{
	char	**argv;
	char	**envp;

	if (!gen_heredoc(ast))
		return (child_free(abs_path), exit(0));
	if (!gen_redirect_in(ast))
		// return (child_free(abs_path), exit(0));
		return (child_free(abs_path), exit(1));
	if (!gen_redirect_out(ast))
		return (child_free(abs_path), exit(0));
	if (!gen_append(ast))
		return (child_free(abs_path), exit(0));
	argv = generate_argv(ast);
	envp = generate_envp();
	// Shouldn't all memory aside from argv and envp not be freed?
	child_free(NULL);
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
	set_exit_status(wstatus, true);
}
