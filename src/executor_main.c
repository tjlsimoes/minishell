/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/13 10:27:20 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_switch(t_ast_node **ast)
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
}

void	builtins_close_fds(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);	// Possible need to check for errors here.
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

void	builtins_exec(t_ast_node **ast)
{
	int			orig_stdin;
	int			orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (!gen_heredoc(ast))
		return (builtins_close_fds(orig_stdin, orig_stdout));
	if (!gen_redirect_out(ast))
		return (builtins_close_fds(orig_stdin, orig_stdout));
	if (!gen_redirect_in(ast))
		return (builtins_close_fds(orig_stdin, orig_stdout));
	if (!gen_append(ast))
		return (builtins_close_fds(orig_stdin, orig_stdout));
	builtins_switch(ast);
	builtins_close_fds(orig_stdin, orig_stdout);
}
// Custom handling of exit could be implemented here
	// else if (ft_strncmp(node->value, "exit",
	//		 ft_strlen(node->value)) == 0)
	// 	ft_exit_exec();

void	exec_switch(t_ast_node **ast)
{
	char	*builtins[7];

	builtins[0] = "cd";
	builtins[1] = "pwd";
	builtins[2] = "echo";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = NULL;
	if (any(builtins, (*ast)->value))
		builtins_exec(ast);
	else
		attempt_path_resolution(ast);
}
// If exit is implemented as a builtin it will have to be
//   added to the above array.

void	alt_child_exec(char *abs_path, t_ast_node **ast, int fd_to_close)
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
		close(fd_to_close);
		exit(0);
	}
	exit(0);
}

void	alt_attempt_path_res(t_ast_node **ast, int fd_to_close)
{
	t_ast_node	*node;
	char		*abs_path;

	node = *ast;
	abs_path = path_resolution(node->value);
	if (!abs_path)
		return ;
	alt_child_exec(abs_path, ast, fd_to_close);
	free(abs_path);
}

void	alt_exec_switch(t_ast_node **ast, int fd_to_close)
{
	char	*builtins[7];

	builtins[0] = "cd";
	builtins[1] = "pwd";
	builtins[2] = "echo";
	builtins[3] = "env";
	builtins[4] = "unset";
	builtins[5] = "export";
	builtins[6] = NULL;
	if (any(builtins, (*ast)->value))
		builtins_exec(ast);
	else
		alt_attempt_path_res(ast, fd_to_close);
}

void	exec_pipe_left(t_ast_node **ast, int fd[2])
{
	close(fd[0]); // Possible error message needed: errno.
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Dup2 error\n", 2)); // Possible error message needed: errno.
	alt_exec_switch(&((*ast)->left), fd[1]);
	close(fd[1]); // Possible error message needed: errno.
	child_free(NULL);
	exit(0);
}

void	exec_pipe_right(t_ast_node **ast, int fd[2])
{
	close(fd[1]); // Possible error message needed: errno.
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (ft_putstr_fd("Dup2 error\n", 2)); // Possible error message needed: errno.
	if ((*ast)->right->type == NODE_PIPE)
		exec_pipe(&((*ast)->right), fd[0]);
	else
		alt_exec_switch(&((*ast)->right), fd[0]);
	close(fd[0]); // Possible error message needed: errno.
	child_free(NULL);
	exit(0);
}

void	exec_pipe(t_ast_node **ast, int	fd_to_close)
{
	int			fd[2];
	int			pid_left;
	int			pid_right;
	int			wstatus;

	if (fd_to_close != -1)
		close(fd_to_close); // Possible error message needed: errno.
	if (!ast || !(*ast))
		return ;
	if (pipe(fd) == -1)
		return (ft_putstr_fd("Pipe error\n", 2)); // Possible error message needed: errno.
	pid_left = fork();
	if (pid_left == -1)
		return (ft_putstr_fd("Fork error\n", 2)); // Possible error message needed: errno.
	if (pid_left == 0)
		return (exec_pipe_left(ast, fd)); // Create child process for execution of command on the left.
	else
	{
		pid_right = fork();
		if (pid_right == -1)
			return (ft_putstr_fd("Fork error\n", 2)); // Possible error message needed: errno.
		if (pid_right == 0)
			return (exec_pipe_right(ast, fd)); // Create child process for execution of command on the right.
	}
	close(fd[0]);
	close(fd[1]);
	// Wait for both child processes, ensuring exit status is updated to the command on the right.
	waitpid(pid_left, &wstatus, 0);
	waitpid(pid_right, &wstatus, 0);	// Not really sure if using an already updated wstatus causes problems.
	set_exit_status(wstatus);
}

void	simple_command_exec(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return ;
	node = *ast;
	if (node->type == NODE_COMMAND)
		return (exec_switch(&node));
	if (node->type == NODE_PIPE && node->right->value
		&& node->right->value[0] == '\0')
		return (exec_switch(&(node->left)));
	if (node->type == NODE_PIPE)
		return (exec_pipe(&node, -1));
}
