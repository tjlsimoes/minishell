/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtins_a.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:06:04 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:07:01 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_exec(t_ast_node **ast)
{
	t_ast_node	*node;
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

int	ft_unset_exec(t_ast_node **ast)
{
	t_ast_node	*node;
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

int	ft_export_exec(t_ast_node **ast)
{
	t_ast_node	*node;
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

int	ft_echo_iter(t_ast_node **ast, bool n)
{
	t_ast_node	*current;
	int			exit_status;

	current = *ast;
	while (current)
	{
		treat_echo_str(&current);
		if (current->right)
		{
			exit_status = ft_echo(current->value, true);
			ft_printf(" ");
		}
		else
			exit_status = ft_echo(current->value, n);
		current = current->right;
	}
	return (exit_status);
}

int	ft_echo_exec(t_ast_node **ast)
{
	t_ast_node	*current;
	bool		n;

	current = *ast;
	n = false;
	if (!current->left || !current->left->value)
		return (ft_echo(NULL, false));
	if (ft_strncmp(current->left->value, "-n", 2) == 0)
	{
		current = current->left->right;
		n = true;
	}
	else
		current = current->left;
	if (!current)
		return (ft_echo(NULL, n));
	return (ft_echo_iter(&current, n));
}
