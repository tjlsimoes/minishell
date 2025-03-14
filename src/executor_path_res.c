/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 19:05:47 by asafrono         ###   ########.fr       */
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
	char			**split;
	int				path_split_need;
	char			*abs_path;

	if (!binary || !*binary)
		return (report_error(ERROR_COMMAND_NOT_FOUND, binary), NULL);
	path_split_need = init_path_vars(&split, binary);
	if (!path_split_need)
		return (NULL);
	else if (path_split_need == 2)
		abs_path = check_absolute_path(binary);
	else if (path_split_need == 3)
		abs_path = gen_path_pwd(binary);
	else if (path_split_need == 4)
		abs_path = gen_path_rel(binary);
	else
		abs_path = path_res_iter(&split, binary);
	return (abs_path);
}

void	child_exec(char *abs_path, t_ast_node **ast)
{
	char	**argv;
	char	**envp;

	if (!gen_redirections(ast))
		return (child_free(abs_path), exit(1));
	argv = generate_argv(ast);
	envp = generate_envp();
	if (minishell_check(ast))
		update_shlvl(envp);
	child_free(NULL);
	if (execve(abs_path, argv, envp) == -1)
	{
		free(abs_path);
		clear_array(argv);
		clear_array(envp);
		exit(1);
	}
	exit(0);
}
// Isn't there a need to free all the structs that are allocated in the
// parent process and "mirrored" in the child process?
// Even if execve doesn't fail?

// Is there a need to restore stdout and stdin if an error occurs?

// Check if command is valid.
// Initial condition was necessary even with gen_path_*
//   functions refactoring in place.
bool	cmd_check(char *abs_path)
{
	struct stat	st;

	if ((stat(abs_path, &st) != 0))
	{
		def_exit(127);
		return (report_error(ERROR_COMMAND_NOT_FOUND, abs_path),
			free(abs_path), true);
	}
	else if (((st.st_mode & S_IFMT) == S_IFDIR))
	{
		def_exit(126);
		return (report_error(ERROR_IS_DIR, abs_path), free(abs_path), true);
	}
	return (false);
}

void	attempt_path_resolution(t_ast_node **ast)
{
	t_ast_node	*node;
	char		*abs_path;
	int			pid;
	int			wstatus;
	void		(*original_sigint)(int); 

	node = *ast;
	abs_path = path_resolution(node->value);
	if (!abs_path || cmd_check(abs_path))
		return ;
	original_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		report_error(ERROR_FORK, "Failed to fork process");
		get_sh()->exit_status = 1;
		set_exit_status(get_sh()->exit_status, false);
		return (free(abs_path));
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_exec(abs_path, ast);
		exit_shell(1, -1, -1);
	}
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, original_sigint); 
	free(abs_path);
	set_exit_status(wstatus, true);
}
