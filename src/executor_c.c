/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:07:15 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/08 11:09:58 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_error_f(char *binary)
{
	ft_putstr_fd(binary, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	path_error_x(char **abs_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*abs_path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free(*abs_path);
}

void	path_error_env(char *binary)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(binary, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

// Returns size of command and its arguments
// Need to increment by one for final NULL
//   on generating an array.
int	get_command_size(t_ASTNode **ast)
{
	t_ASTNode	*node;
	int			size;

	if (!ast || !(*ast))
		return (0);
	node = *ast;
	size = 1;
	if (node->left)
		size++;
	else
		return (size);
	node = node->left->right;
	while (node)
	{
		size++;
		node = node->right;
	}
	return (size);
}

void	clear_array_idx(char **array, int idx)
{
	while (idx > 0)
		free(array[--idx]);
	free(array);
}
