/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:44 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 18:42:03 by asafrono         ###   ########.fr       */
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

// Check if 'array' contains an exact match
//   to 'value'.
// Returns true if match is found.
// Returns false if it isn't found or if it
//   receives invalid arguments.
bool	any(char **array, char *value)
{
	int		i;

	if (!value || !array || !(*array))
		return (false);
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(value, array[i], ft_strlen(value)) == 0
			&& array[i][ft_strlen(value)] == '\0')
			return (true);
		i++;
	}
	return (false);
}

void	child_free(char *abs_path)
{
	ft_lstdel(&(get_sh()->env_var));
	free_tokens(get_sh()->tokens);
	free_ast(get_sh()->ast);
	free(get_sh()->input);
	free(abs_path);
}

void	treat_echo_str(t_ast_node **ast)
{
	if ((*ast)->quote_char != '\'')
		expand_env_var(&((*ast)->value));
}
