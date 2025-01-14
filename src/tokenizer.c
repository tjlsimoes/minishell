/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:56 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/14 14:48:31 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Processes input text to tokenize it while handling quotes and whitespace,
// storing tokens in a provided token information structure. 
void	process_input(const char *input, t_token_info *info)
{
	int		i;
	bool	in_quote;
	char	quote_char;

	i = -1;
	in_quote = false;
	quote_char = '\0';
	while (input[++i] != '\0')
	{
		if ((input[i] == '\'' || input[i] == '\"') && !in_quote)
		{
			in_quote = true;
			quote_char = input[i];
		}
		else if (input[i] == quote_char && in_quote)
			in_quote = false;
		else if (ft_isspace(input[i]) && !in_quote && info->token_length > 0)
		{
			info->current_token[info->token_length] = '\0';
			info->tokens[(info->index)++] = ft_strdup(info->current_token);
			info->token_length = 0;
			continue ;
		}
		info->current_token[(info->token_length)++] = input[i];
	}
}

// Tokenizes a given input string into an array of strings (tokens)
// based on whitespace and quotes, returning the array of tokens. 
char	**tokenize_input(const char *input)
{
	t_token_info	info;
	char			current_token[MAX_INPUT_LENGTH];

	info.tokens = malloc(MAX_INPUT_LENGTH * sizeof(char *));
	if (!info.tokens)
		return (NULL);
	info.index = 0;
	info.token_length = 0;
	info.current_token = current_token;
	process_input(input, &info);
	if (info.token_length > 0)
	{
		info.current_token[info.token_length] = '\0';
		info.tokens[info.index++] = ft_strdup(info.current_token);
	}
	info.tokens[info.index] = NULL;
	return (info.tokens);
}
