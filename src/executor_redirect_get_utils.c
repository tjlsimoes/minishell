/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_get_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:00:44 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/18 11:35:08 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_rm_quotes_len(char **str)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;
	int		k;

	if (!str || (!idx((*str), '\'' ) && !idx((*str), '"' )))
		return (0);
	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	k = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((*str)[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			k++;
		i++;
	}
	return (k);
}

void	rm_quotes_gen_res(char **str, char **result)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;
	int		k;

	if (!str || !(*str) || !result)
		return ;
	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	k = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((*str)[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			(*result)[k++] = (*str)[i];
		i++;
	}
	(*result)[k] = '\0';
}

int	alt_rm_quotes(char **str)
{
	char	*result;

	if (!str || (!idx((*str), '\'' ) && !idx((*str), '"' )))
		return (1);
	result = ft_calloc(1, get_rm_quotes_len(str) + 1);
	if (!result)
		return (0);
	rm_quotes_gen_res(str, &result);
	free((*str));
	*str = result;
	return (1);
}
