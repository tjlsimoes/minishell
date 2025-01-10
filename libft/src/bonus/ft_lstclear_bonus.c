/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:02:30 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 13:57:28 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst && del)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			del(current->content);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}

// static t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new_node;

// 	new_node = (t_list *)malloc(sizeof(t_list));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->content = content;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// static void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*last;

// 	if (lst)
// 	{
// 		if (*lst)
// 		{
// 			last = *lst;
// 			while (last->next)
// 				last = last->next;
// 			last->next = new;
// 		}
// 		else
// 			*lst = new;
// 	}
// }

// static void	print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s -> ", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// static void	del_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*list;
// 	char	*str1;
// 	char	*str2;
// 	char	*str3;

// 	list = NULL;

// 	str1 = strdup("Hello");
// 	str2 = strdup("World");
// 	str3 = strdup("!");

// 	ft_lstadd_back(&list, ft_lstnew(str1));
// 	ft_lstadd_back(&list, ft_lstnew(str2));
// 	ft_lstadd_back(&list, ft_lstnew(str3));

// 	printf("Initial list: ");
// 	print_list(list);

// 	printf("Clearing the list...\n");
// 	ft_lstclear(&list, del_content);

// 	printf("List after clearing: ");
// 	if (list == NULL)
// 		printf("NULL\n");
// 	else
// 		print_list(list);

// 	return (0);
// }
