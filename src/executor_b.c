/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:36:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/08 11:17:18 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_iter(t_ASTNode **ast, bool n)
{
	t_ASTNode	*current;
	int			exit_status;

	current = *ast;
	while (current)
	{
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

int	ft_echo_exec(t_ASTNode **ast)
{
	t_ASTNode	*current;
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
