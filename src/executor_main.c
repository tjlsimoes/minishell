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

void	builtins_exec(t_ast_node **ast)
{
	int			orig_stdin;
	int			orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (!gen_redirect_out(ast))
		return ;
	if (!gen_redirect_in(ast))
		return ;
	if (!gen_append(ast))
		return ;
	builtins_switch(ast);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
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

void	simple_command_exec(t_ast_node **ast)
{
	t_ast_node	*node;

	if (!ast || !(*ast))
		return ;
	node = *ast;
	if (node->type == NODE_COMMAND)
		exec_switch(&node);
}
