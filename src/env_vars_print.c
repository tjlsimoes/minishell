/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:07:19 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:00:12 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_vars(t_list **lst)
{
	t_list	*node;

	if (!lst || !(*lst))
		return ;
	node = *lst;
	while (node)
	{
		write(1, node->content, ft_strlen(node->content));
		write(1, "\n", 1);
		node = node->next;
	}
}

