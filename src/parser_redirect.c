/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/09 13:26:19 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_redirect_fd(char *token)
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

static t_node_type	get_redirect_type(char *token,
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

static char	*get_filename(char **tokens,
		int *index, char *redirect_s, int op_len)
{
	char	*filename;
	char	*cleaned_filename;

	if (redirect_s && *(redirect_s + op_len) != '\0')
	{
		filename = ft_strdup(redirect_s + op_len);
		(*index)++;
	}
	else if (tokens[(*index) + 1])
	{
		filename = ft_strdup(tokens[(*index) + 1]);
		(*index) += 2;
	}
	else
	{
		(*index)++;
		report_error(ERROR_SYNTAX, "newline");
		return (NULL);
	}
	cleaned_filename = clean_arg(filename);
	free(filename);
	return (cleaned_filename);
}

static t_ast_node	*create_redirect_node(char **tokens, int *index)
{
	t_node_type	redirect_type;
	char		*redirect_s;
	int			op_len;
	int			fd;
	char		*filename;

	redirect_type = get_redirect_type(tokens[*index], &redirect_s, &op_len);
	fd = parse_redirect_fd(tokens[*index]);
	filename = get_filename(tokens, index, redirect_s, op_len);
	if (!filename)
		return (NULL);
	return (create_node(redirect_type, filename, fd));
}

t_ast_node	*parse_redirect_node(char **tokens,
				int *index, t_ast_node *cmd_node)
{
	t_ast_node	*redirect_node;
	t_ast_node	**current;

	redirect_node = create_redirect_node(tokens, index);
	if (!redirect_node)
		return (NULL);
	current = &cmd_node->right;
	while (*current)
		current = &(*current)->right;
	*current = redirect_node;
	return (redirect_node);
}
