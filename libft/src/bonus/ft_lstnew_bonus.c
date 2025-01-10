/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:02:55 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/20 13:57:43 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// static void	print_int_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%d -> ", *(int *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// static void	print_str_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s -> ", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// int	main(void)
// {
// 	t_list	*node;
// 	int num = 42;
// 	char *str = "Hello, World!";

//     // Test 1: Create a node with integer content
// 	node = ft_lstnew(&num);
// 	if (node)
// 	{
// 		printf("Test 1 - Integer node: ");
// 		print_int_list(node);
// 		free(node);
// 	}
// 	else
// 		printf("Test 1 failed: Node creation failed\n");
// 	// Test 2: Create a node with string content
// 	node = ft_lstnew(str);
// 	if (node)
// 	{
// 		printf("Test 2 - String node: ");
// 		print_str_list(node);
// 		free(node);
// 	}
// 	else
// 		printf("Test 2 failed: Node creation failed\n");
// 	// Test 3: Create a node with NULL content
// 	node = ft_lstnew(NULL);
// 	if (node)
// 	{
// 		printf("Test 3 - NULL content node created successfully\n");
// 		free(node);
// 	}
// 	else
// 		printf("Test 3 failed: Node creation failed\n");
// 	return (0);
// }
