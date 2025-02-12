/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:46:10 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 12:52:13 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strs_join(char **array)
{
	int		i;
	char	*result;

	if (!array || !(*array))
		return (NULL);
	result = NULL;
	result = alt_strjoin(result, array[0]);
	i = 0;
	while (array[i])
	{
		result = alt_strjoin(result, array[i + 1]);
		i++;
	}
	return (result);
}

void	*clear_array(char **array)
{
	int	j;

	if (!array || !(*array))
		return (NULL);
	j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}

int	special_chars(char c)
{
	if (c == '*' || c == '@' || c == '#'
		|| c == '-' || c == '$' || c == '!')
		return (1);
	return (0);
}
// || c == '0')

// Delete linked list with each node's content
// also freed.
void	ft_lstdel(t_list **lst)
{
	t_list	*previous_node;
	t_list	*current_node;

	if (!lst)
		return ;
	current_node = *lst;
	while (current_node != NULL)
	{
		previous_node = current_node;
		free(previous_node->content);
		current_node = previous_node->next;
		free(previous_node);
		previous_node = NULL;
	}
	*lst = NULL;
}
