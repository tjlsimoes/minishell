/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:05:48 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/06 18:56:30 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_exec(t_ASTNode **ast)
{
	t_ASTNode	*node;
	char		*str;
	int			exit_status;

	node = *ast;
	str = NULL;
	exit_status = 42;
	if (!node->left)
	{
		exit_status = ft_cd(&str);
		free(str);
		return (exit_status);
	}
	if (node->left->right)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	return (ft_cd(&(node->left->value)));
}
// No possibility of there being node->left->right where node->left is NULL,
// right?

int	ft_unset_exec(t_ASTNode **ast)
{
	t_ASTNode	*node;
	int			exit_status;

	node = *ast;
	if (!node->left)
		return (0);
	exit_status = ft_unset(node->left->value);
	node = node->left->right;
	while (node)
	{
		exit_status = ft_unset(node->value);
		node = node->right;
	}
	return (exit_status);
}

int	ft_export_exec(t_ASTNode **ast)
{
	t_ASTNode	*node;
	int			exit_status;
	int			temp;

	node = *ast;
	if (!node->left)
		return (0);
	exit_status = ft_export(&(node->left->value));
	node = node->left->right;
	while (node)
	{
		temp = ft_export(&(node->value));
		if (exit_status == 0)
			exit_status = temp;
		node = node->right;
	}
	return (exit_status);
}

void	builtins_switch(t_ASTNode **ast)
{
	t_ASTNode	*node;
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
	else
		attempt_path_resolution(ast);
}
// Custom handling of exit could be implemented here
	// else if (ft_strncmp(node->value, "exit", ft_strlen(node->value)) == 0)
	// 	ft_exit_exec();

void	simple_command_exec(t_ASTNode **ast)
{
	t_ASTNode	*node;

	if (!ast || !(*ast))
		return ;
	node = *ast;
	if (node->type == NODE_COMMAND)
		builtins_switch(&node);
}
