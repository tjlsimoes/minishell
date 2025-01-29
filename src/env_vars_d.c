/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:08:16 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/01/29 14:09:39 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// Get index of non-NULL character c within parameter str.
int	idx(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (*str)
	{
		if (*str == (char)c)
			return (i);
		i++;
		str++;
	}
	return (-1);
}

void	free_node(t_list **node_adrr)
{
	t_list	*node;

	node = *node_adrr;
	free(node->content);
	free(node);
	node = NULL;
}

char	*alt_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	int		i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	i = ft_strcpy(str, (char *)s1, i);
	i = ft_strcpy(str, (char *)s2, s1_len);
	str[i] = '\0';
	if (s1_len > 0)
		free(s1);
	return (str);
}

int	ft_strcpy(char *str, char *s, int start)
{
	int		i;

	i = start;
	if (s)
	{
		while (s[i - start] != '\0')
		{
			str[i] = s[i - start];
			i++;
		}
	}
	return (i);
}
