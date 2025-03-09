/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:07:19 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 11:46:25 by asafrono         ###   ########.fr       */
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
