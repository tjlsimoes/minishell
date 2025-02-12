/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:44 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:08:28 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns size of command and its arguments
// Need to increment by one for final NULL
//   on generating an array.
int	get_command_size(t_ast_node **ast)
{
	t_ast_node	*node;
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
