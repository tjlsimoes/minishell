/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 12:29:05 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_switch(t_ast_node **ast, int orig_stdin,
		int orig_stdout, int fd_to_close)
{
	t_ast_node	*node;
	t_minishell	*sh;

	node = *ast;
	sh = get_sh();
	if (ft_strncmp(node->value, "cd", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_cd_exec(ast);
	else if (ft_strncmp(node->value, "pwd", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_pwd();
	else if (ft_strncmp(node->value, "echo", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_echo_exec(ast);
	else if (ft_strncmp(node->value, "env", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_env(&(sh->env_var));
	else if (ft_strncmp(node->value, "unset", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_unset_exec(ast);
	else if (ft_strncmp(node->value, "export", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_export_exec(ast);
	else if (ft_strncmp(node->value, "exit", ft_strlen(node->value)) == 0)
		sh->exit_status = ft_exit_exec(node->left, orig_stdin,
				orig_stdout, fd_to_close);
	set_exit_status(sh->exit_status, false);
}

void	builtins_close_fds(int orig_stdin, int orig_stdout, int fd_to_close)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	if (orig_stdin >= 0)
		close(orig_stdin);
	if (orig_stdout >= 0)
		close(orig_stdout);
	if (fd_to_close >= 0)
		close(fd_to_close);
}

void	builtins_exec(t_ast_node **ast, int fd_to_close)
{
	int			orig_stdin;
	int			orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (!gen_redirections(ast))
		return (def_exit(1),
			builtins_close_fds(orig_stdin, orig_stdout, fd_to_close));
	builtins_switch(ast, orig_stdin, orig_stdout, fd_to_close);
	builtins_close_fds(orig_stdin, orig_stdout, fd_to_close);
}

void	exec_switch(t_ast_node **ast)
{
	char	*builtins[8];

	builtins[0] = "cd";
	builtins[1] = "pwd";
	builtins[2] = "echo";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = "exit";
	builtins[7] = NULL;
	if (any(builtins, (*ast)->value))
		builtins_exec(ast, -2);
	else
		attempt_path_resolution(ast);
}
// If exit is implemented as a builtin it will have to be
//   added to the above array.

void	alt_child_exec(char *abs_path, t_ast_node **ast, int fd_to_close)
{
	char	**argv;
	char	**envp;

	if (!gen_redirections(ast))
		return (child_free(abs_path), close(fd_to_close), exit(1));
	argv = generate_argv(ast);
	envp = generate_envp();
	child_free(NULL);
	if (execve(abs_path, argv, envp) == -1)
	{
		free(abs_path);
		clear_array(argv);
		clear_array(envp);
		close(fd_to_close);
		exit(1);
	}
	exit(127);
}
