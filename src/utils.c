/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:18 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 15:05:02 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Determines if a given token is a redirection operator (<, >, or >>),
// returning a boolean value indicating whether it is a redirect. 
int	is_redirect(char *token)
{
	int i;

	if (!token)
		return (0);
	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	return (ft_strncmp(token + i, "<", 1) == 0 || ft_strncmp(token + i, ">", 1) == 0
		|| ft_strncmp(token + i, ">>", 2) == 0 || ft_strncmp(token + i, "<<", 2) == 0);
}

void	free_tokens(char **tokens)
{
	int i;
	if (!tokens)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
