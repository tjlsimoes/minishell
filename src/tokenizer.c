/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:02:56 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/14 17:33:09 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Processes input text to tokenize it while handling quotes and whitespace,
// storing tokens in a provided token information structure.

void	handle_quote(const char *input, int *i,
			t_token_info *info, bool *in_quote)
{
	if (!(*in_quote))
		info->quote_char = '\0';
	if ((input[*i] == '\'' || input[*i] == '\"') && !(*in_quote))
	{
		*in_quote = true;
		info->quote_char = input[*i];
		info->current_token[(info->token_length)++] = input[*i];
	}
	else if (input[*i] == info->quote_char && *in_quote)
	{
		*in_quote = false;
		info->current_token[(info->token_length)++] = input[*i];
		info->quote_char = '\0';
	}
	else if (!ft_isspace(input[*i]) || *in_quote)
		info->current_token[(info->token_length)++] = input[*i];
}

void	handle_operator(const char *input, int *i, t_token_info *info)
{
	if (info->token_length > 0)
	{
		info->current_token[info->token_length] = '\0';
		info->tokens[(info->index)++] = ft_strdup(info->current_token);
		info->token_length = 0;
	}
	info->current_token[0] = input[*i];
	info->token_length = 1;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		info->current_token[1] = input[++(*i)];
		info->token_length = 2;
	}
	info->current_token[info->token_length] = '\0';
	info->tokens[(info->index)++] = ft_strdup(info->current_token);
	info->token_length = 0;
}

int	process_input(const char *input, t_token_info *info)
{
	int		i;
	bool	in_q;
	bool	has_non_whitespace;

	i = -1;
	in_q = false;
	while (input[++i] != '\0')
	{
		has_non_whitespace = !ft_isspace(input[i]);
		if (!in_q && (input[i] == '|' || input[i] == '<' || input[i] == '>'))
			handle_operator(input, &i, info);
		else
		{
			handle_quote(input, &i, info, &in_q);
			if (ft_isspace(input[i]) && !in_q && info->token_length > 0)
			{
				info->current_token[info->token_length] = '\0';
				info->tokens[(info->index)++] = ft_strdup(info->current_token);
				info->token_length = 0;
			}
		}
	}
	if (in_q)
		return (report_error(ERROR_UNCLOSED_QUOTE, NULL), 0);
	return (has_non_whitespace);
}

// Tokenizes a given input string into an array of strings (tokens)
// based on whitespace and quotes, returning the array of tokens.
char	**tokenize_input(const char *input)
{
	t_token_info	info;
	char			current_token[MAX_INPUT_LENGTH];

	info.tokens = ft_calloc(MAX_INPUT_LENGTH, sizeof(char *));
	if (!info.tokens)
		return (NULL);
	info.index = 0;
	info.token_length = 0;
	info.current_token = current_token;
	info.quote_char = '\0';
	if (!process_input(input, &info))
		return (free_tokens(info.tokens), NULL);
	if (info.token_length > 0)
	{
		info.current_token[info.token_length] = '\0';
		info.tokens[info.index++] = ft_strdup(info.current_token);
	}
	info.tokens[info.index] = NULL;
	return (info.tokens);
}

//This function takes a user input string, tokenizes it into an array of
//tokens, constructs an abstract syntax tree (AST) from those tokens,
//prints the AST structure, and then frees the allocated memory for tokens&AST.
void	process_tokens(char *input)
{
	t_minishell	*sh;

	sh = get_sh();
	sh->tokens = tokenize_input(input);
	if (sh->tokens && sh->tokens[0] != NULL)
	{
		sh->ast = parse(sh->tokens);
		simple_command_exec(&(sh->ast));
		free_tokens(sh->tokens);
		free_ast(sh->ast);
	}
	else if (sh->tokens)
		free_tokens(sh->tokens);
}

// void	process_tokens(char *input)
// {
// 	t_minishell	*sh;

// 	sh = get_sh();
// 	sh->tokens = tokenize_input(input);
// 	if (sh->tokens)
// 	{
// 		sh->ast = parse(sh->tokens);
// 		pretty_print_ast(sh->ast, 0);
// 		simple_command_exec(&(sh->ast));
// 		free_tokens(sh->tokens);
// 		free_ast(sh->ast);
// 	}
// }
