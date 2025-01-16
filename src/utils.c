/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:18 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/16 17:00:46 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Determines if a given token is a redirection operator (<, >, or >>),
// returning a boolean value indicating whether it is a redirect. 
int	is_redirect(char *token)
{
	return (ft_strncmp(token, "<", 2) == 0 || ft_strncmp(token, ">", 2) == 0
		|| ft_strncmp(token, ">>", 2) == 0);
}
