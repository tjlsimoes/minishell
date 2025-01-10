/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:02:47 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 13:57:35 by asafrono         ###   ########.fr       */
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

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
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

// static void	to_uppercase(void *content)
// {
// 	char	*str;
// 	int		i;

// 	str = (char *)content;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] >= 'a' && str[i] <= 'z')
// 			str[i] = str[i] - 32;
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	t_list	*list;
// 	char	*str1;
// 	char	*str2;
// 	char	*str3;

// 	list = NULL;

// 	str1 = strdup("hello");
// 	str2 = strdup("world");
// 	str3 = strdup("42");

// 	ft_lstadd_back(&list, ft_lstnew(str1));
// 	ft_lstadd_back(&list, ft_lstnew(str2));
// 	ft_lstadd_back(&list, ft_lstnew(str3));

// 	printf("Initial list: ");
// 	print_list(list);

// 	printf("Applying to_uppercase function...\n");
// 	ft_lstiter(list, to_uppercase);

// 	printf("List after applying function: ");
// 	print_list(list);

// 	while (list)
// 	{
// 		t_list *temp = list;
// 		list = list->next;
// 		free(temp->content);
// 		free(temp);
// 	}

// 	return (0);
// }
