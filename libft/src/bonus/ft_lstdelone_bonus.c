/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:02:43 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 13:57:31 by asafrono         ###   ########.fr       */
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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
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

// t_list	*ft_lstlast(t_list *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// int	main(void)
// {
// 	t_list	*list;
// 	t_list	*node_to_delete;
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

// 	// Delete the last node
// 	node_to_delete = ft_lstlast(list);

// 	// Find the second-to-last node
// 	t_list *second_to_last = list;
// 	while (second_to_last->next && second_to_last->next != node_to_delete)
// 		second_to_last = second_to_last->next;

// 	// Update the list
// 	if (second_to_last == list && second_to_last->next == node_to_delete)
// 		list = NULL;
// 	else
// 		second_to_last->next = NULL;

// 	printf("Deleting node with content '%s'\n",
// 				(char *)node_to_delete->content);
// 	ft_lstdelone(node_to_delete, del_content);

// 	printf("List after deletion: ");
// 	print_list(list);

// 	// Clean up the remaining list
// 	while (list)
// 	{
// 		t_list *temp = list;
// 		list = list->next;
// 		ft_lstdelone(temp, del_content);
// 	}

// 	return (0);
// }
