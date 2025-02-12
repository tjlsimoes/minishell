/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_change.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:21 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:00:07 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_var(t_list **lst, char *content)
{
	if (!lst)
		return ;
	if (!update_env_var(lst, content))
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(content)));
}

void	del_env_var(t_list **lst, char *content)
{
	t_list	*previous;
	t_list	*current;

	if (!lst || !(*lst) || !content)
		return ;
	current = *lst;
	if (is_key(current, content))
	{
		*lst = current->next;
		free_node(&current);
		return ;
	}
	while (current)
	{
		previous = current;
		current = previous->next;
		if (is_key(current, content))
		{
			previous->next = current->next;
			free_node(&current);
			return ;
		}
	}
}

// Update environment variable if a match with
// its NAME is verified.
// Return 1 if an update is made.
// Return 0 if an update isn't made.
int	update_env_var(t_list **lst, char *content)
{
	t_list	*node;
	char	*key;

	if (!lst || !(*lst))
		return (0);
	node = *lst;
	key = get_env_key(content);
	while (node)
	{
		if (is_key(node, key))
		{
			free(key);
			key = NULL;
			free(node->content);
			node->content = ft_strdup(content);
			return (1);
		}
		node = node->next;
	}
	free(key);
	key = NULL;
	return (0);
}
