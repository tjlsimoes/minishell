/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:34 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/04 20:24:07 by asafrono         ###   ########.fr       */
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
	dup2(orig_stdin, STDIN_FILENO);	// Possible need to check for errors here.
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
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
	if (!gen_heredoc(ast))
		return (def_exit(1), builtins_close_fds(orig_stdin, orig_stdout, fd_to_close));
	if (!gen_redirect_stdout(ast))
		return (def_exit(1), builtins_close_fds(orig_stdin, orig_stdout, fd_to_close));
	if (!gen_redirect_in(ast))
		return (def_exit(1), builtins_close_fds(orig_stdin, orig_stdout, fd_to_close));
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

	if (!gen_heredoc(ast))
		return (child_free(abs_path), close(fd_to_close), exit(1));
	if (!gen_redirect_in(ast))
		return (child_free(abs_path), close(fd_to_close), exit(1));
	if (!gen_redirect_stdout(ast))
		return (child_free(abs_path), close(fd_to_close), exit(1));
	argv = generate_argv(ast);
	envp = generate_envp();
	// Shouldn't all memory aside from argv and envp not be freed?
	child_free(NULL);
	if (execve(abs_path, argv, envp) == -1)
	{
		free(abs_path);
		clear_array(argv);
		clear_array(envp);
		close(fd_to_close);
		exit(1);
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
		builtins_exec(ast, fd_to_close);
	else
		alt_attempt_path_res(ast, fd_to_close);
}

void	exec_pipe_child_exit(int fd_to_close, char *error_msg)
{
	close(fd_to_close); // Possible error message needed: errno.
	child_free(NULL);
	if (error_msg)
		report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
	exit(0);
}

void	exec_pipe_left(t_ast_node **ast, int fd[2])
{
	close(fd[0]); // Possible error message needed: errno.
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (exec_pipe_child_exit(fd[1], "Dup2 error\n")); // Possible error message needed: errno.
	alt_exec_switch(&((*ast)->left), fd[1]);
	exec_pipe_child_exit(fd[1], NULL);
}

void	exec_pipe_right(t_ast_node **ast, int fd[2])
{
	close(fd[1]); // Possible error message needed: errno.
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (exec_pipe_child_exit(fd[0], "Dup2 error\n")); // Possible error message needed: errno.
	if ((*ast)->right->type == NODE_PIPE)
		exec_pipe(&((*ast)->right), fd[0]);
	else
		alt_exec_switch(&((*ast)->right), fd[0]);
	exec_pipe_child_exit(fd[0], NULL);
}

// void	exec_pipe(t_ast_node **ast, int	fd_to_close)
// {
// 	int			fd[2];
// 	int			pid_left;
// 	int			pid_right;
// 	int			wstatus;

// 	if (fd_to_close != -1)
// 		close(fd_to_close); // Possible error message needed: errno.
// 	if (!ast || !(*ast))
// 		return ;
// 	if (pipe(fd) == -1)
// 		return (report_error(ERROR_PIPE, "Failed to create pipe")); // Possible error message needed: errno.
// 	pid_left = fork();
// 	if (pid_left == -1)
// 		return (report_error(ERROR_FORK, "Failed to fork process")); // Possible error message needed: errno.
// 	if (pid_left == 0)
// 		return (exec_pipe_left(ast, fd)); // Create child process for execution of command on the left.
// 	else
// 	{
// 		pid_right = fork();
// 		if (pid_right == -1)
// 			return (report_error(ERROR_FORK, "Failed to fork process")); // Possible error message needed: errno.
// 		if (pid_right == 0)
// 			return (exec_pipe_right(ast, fd)); // Create child process for execution of command on the right.
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	// Wait for both child processes, ensuring exit status is updated to the command on the right.
// 	waitpid(pid_left,  &wstatus, 0);
// 	waitpid(pid_right, &wstatus, 0);	// Not really sure if using an already updated wstatus causes problems.
// 	set_exit_status(wstatus, true);
// }

void exec_pipe(t_ast_node **ast, int fd_to_close)
{
	int fd[2];
	pid_t pid_left;
	pid_t pid_right;
	int wstatus;

	if (fd_to_close != -1)
		close(fd_to_close);
	if (!ast || !*ast)
		return;
	if (pipe(fd) == -1)
		return(report_error(ERROR_PIPE, "Failed to create pipe"));
	pid_left = fork();
	if (pid_left == -1)
		return(report_error(ERROR_FORK, "Failed to fork process"));
	if (pid_left == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
			exit_shell(1, fd[1], -1, -1);
		}
		close(fd[1]);
		alt_exec_switch(&((*ast)->left), -1);
		exit_shell(get_sh()->exit_status, -1, -1, -1);
	}
	pid_right = fork();
	if (pid_right == -1)
	{
		kill(pid_left, SIGTERM);
		waitpid(pid_left, NULL, 0);
		return(report_error(ERROR_FORK, "Failed to fork process"));
	}
	if (pid_right == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1) {
			report_error(ERROR_DUP2, "Failed to duplicate file descriptor");
			exit_shell(1, -1, fd[0], -1);
		}
		close(fd[0]);
		if ((*ast)->right->type == NODE_PIPE)
			exec_pipe(&((*ast)->right), -1);
		else
			alt_exec_switch(&((*ast)->right), -1);
		exit_shell(get_sh()->exit_status, -1, -1, -1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &wstatus, 0);
	get_sh()->exit_status = WEXITSTATUS(wstatus);
	set_exit_status(get_sh()->exit_status, false);
}

void	simple_command_exec(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return ;
	node = *ast;
	if (node->type == NODE_COMMAND)
		return (exec_switch(&node));
	else if (node->type == NODE_PIPE && node->right->value
		&& node->right->value[0] == '\0')
		return (exec_switch(&(node->left)));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(&node, -1));
}
