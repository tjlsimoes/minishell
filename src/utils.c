/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:18 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/13 18:16:32 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Determines if a given token is a redirection operator (<, >, or >>),
// returning a boolean value indicating whether it is a redirect. 
int	is_redirect(char *token)
{
	int	i;

	if (!token)
		return (0);
	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	return (ft_strncmp(token + i, "<", 1) == 0
		|| ft_strncmp(token + i, ">", 1) == 0
		|| ft_strncmp(token + i, ">>", 2) == 0
		|| ft_strncmp(token + i, "<<", 2) == 0);
}

void	free_tokens(char **tokens)
{
	int	i;

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

// char	*replace_substring(char *str, int start, int len, char *replacement)
// {
// 	char	*result;
// 	int		new_len;

// 	new_len = ft_strlen(str) - len + ft_strlen(replacement);
// 	result = ft_calloc(new_len + 1, 0);
// 	ft_strlcpy(result, str, start + 1);
// 	ft_strlcat(result, replacement, new_len + 1);
// 	ft_strlcat(result, str + start + len, new_len + 1);
// 	free(str);
// 	return (result);
// }
