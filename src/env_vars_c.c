/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:07:49 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/15 11:09:31 by tjorge-l         ###   ########.fr       */
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

// Check if passed env variable NAME (taken here to be synonymous
// to the concept of 'key') matches value passed in str parameter.
// Returns 1 if str == 'NAME' matching environment variable 'NAME=...'
// Otherwise it returns 0.
int	is_key(t_list *env_var, char *str)
{
	int	str_len;

	if (!env_var || !str)
		return (0);
	str_len = ft_strlen(str);
	if (ft_strncmp(env_var->content, str, str_len) == 0
		&& ((char *)env_var->content)[str_len] == '=')
		return (1);
	return (0);
}
