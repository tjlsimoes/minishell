/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:02:52 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 13:57:40 by asafrono         ###   ########.fr       */
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

// static t_list    *ft_lstnew(void *content);
// static void     ft_lstadd_back(t_list **lst, t_list *new);
// static void     ft_lstclear(t_list **lst, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			del(new_content);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
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

// void	ft_lstadd_back(t_list **lst, t_list *new)
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

// static void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*current;
// 	t_list	*next;

// 	if (lst && del)
// 	{
// 		current = *lst;
// 		while (current)
// 		{
// 			next = current->next;
// 			del(current->content);
// 			free(current);
// 			current = next;
// 		}
// 		*lst = NULL;
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

// static void	*to_uppercase(void *content)
// {
// 	char	*str;
// 	char	*new_str;
// 	int		i;

// 	str = (char *)content;
// 	new_str = strdup(str);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (new_str[i])
// 	{
// 		if (new_str[i] >= 'a' && new_str[i] <= 'z')
// 			new_str[i] = new_str[i] - 32;
// 		i++;
// 	}
// 	return (new_str);
// }

// static void	del_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*list;
// 	t_list	*mapped_list;
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

// 	printf("Original list: ");
// 	print_list(list);

// 	mapped_list = ft_lstmap(list, to_uppercase, del_content);

// 	printf("Mapped list: ");
// 	print_list(mapped_list);

// 	ft_lstclear(&list, del_content);
// 	ft_lstclear(&mapped_list, del_content);

// 	return (0);
// }
