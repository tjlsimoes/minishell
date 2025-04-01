/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/13 22:20:39 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirect_fd(char *token)
{
	int		i;
	int		fd;
	char	*fd_str;

	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	if (i == 0 && ft_strchr("><", token[i]))
	{
		if (token[i] == '>')
			return (STDOUT_FILENO);
		return (STDIN_FILENO);
	}
	fd_str = ft_substr(token, 0, i);
	fd = ft_atoi(fd_str);
	free(fd_str);
	return (fd);
}

t_node_type	get_redirect_type(char *token,
		char **symbol_ptr, int *op_len)
{
	int	i;

	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	*op_len = 1;
	*symbol_ptr = &token[i];
	if (ft_strncmp(*symbol_ptr, ">>", 2) == 0)
	{
		*op_len = 2;
		return (NODE_REDIRECT_APPEND);
	}
	else if (ft_strncmp(*symbol_ptr, "<<", 2) == 0)
	{
		*op_len = 2;
		return (NODE_HEREDOC);
	}
	else if (ft_strncmp(*symbol_ptr, ">", 1) == 0)
		return (NODE_REDIRECT_OUT);
	else if (ft_strncmp(*symbol_ptr, "<", 1) == 0)
		return (NODE_REDIRECT_IN);
	*op_len = 0;
	return (NODE_COMMAND);
}

char	*get_filename(char **tokens,
		int *index, char *redirect_s, int op_len)
{
	char	*filename;

	if (redirect_s && *(redirect_s + op_len) != '\0')
	{
		filename = ft_strdup(redirect_s + op_len);
		(*index)++;
	}
	else if (tokens[(*index) + 1] && !is_redirect(tokens[(*index) + 1]))
	{
		filename = ft_strdup(tokens[(*index) + 1]);
		(*index) += 2;
	}
	else
		return (NULL);
	return (filename);
}

// Helper function to extract redirection metadata
int	get_redirect_metadata(char *token, t_node_type *redirect_type,
		char **redirect_s, int *op_len)
{
	*redirect_type = get_redirect_type(token, redirect_s, op_len);
	return (parse_redirect_fd(token));
}

// Helper function to create an AST node with the filename
t_ast_node	*create_redirect_ast_node(char **tokens, int *index,
		t_node_type redirect_type, int fd)
{
	char		*filename;
	char		*cleaned_filename;
	t_ast_node	*node;

	filename = get_filename(tokens, index, NULL, 0);
	if (!filename)
	{
		(*index)++;
		report_error(ERROR_SYNTAX, "newline");
		return (def_exit(2), NULL);
	}
	cleaned_filename = clean_arg(filename);
	node = create_node(redirect_type, cleaned_filename, fd);
	if (filename && filename[0] == '\'')
		node->quote_char = '\'';
	else if (filename && filename[0] == '"')
		node->quote_char = '"';
	else
		node->quote_char = 'N';
	free(cleaned_filename);
	free(filename);
	return (node);
}
