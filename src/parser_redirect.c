/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/23 13:15:45 by asafrono         ###   ########.fr       */
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
	if (i == 0)
	{
		if (ft_strchr("><", token[i]))
		{
			if (token[i] == '>')
				return (STDOUT_FILENO);
			return (STDIN_FILENO);
		}
	}
	fd_str = ft_substr(token, 0, i);
	fd = ft_atoi(fd_str);
	free(fd_str);
	return (fd);
}

static t_node_type	get_redirect_type_and_symbol(char *token, char **symbol_ptr)
{
	int	i;

	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	*symbol_ptr = &token[i];
	if (ft_strncmp(*symbol_ptr, ">>", 2) == 0)
		return (NODE_REDIRECT_APPEND);
	if (ft_strncmp(*symbol_ptr, "<<", 2) == 0)
		return (NODE_HEREDOC);
	if (ft_strncmp(*symbol_ptr, "<", 1) == 0)
		return (NODE_REDIRECT_IN);
	if (ft_strncmp(*symbol_ptr, ">", 1) == 0)
		return (NODE_REDIRECT_OUT);
	*symbol_ptr = NULL;
	return (NODE_COMMAND);
}

static void	attach_redirect(t_ast_node *cmd_node, t_ast_node *redirect_node)
{
	t_ast_node	**current;

	current = &cmd_node->right;
	while (*current)
		current = &(*current)->right;
	*current = redirect_node;
}

static char	*get_filename(char **tokens, int *index, char *redirect_s)
{
	char	*filename;
	char	*cleaned_filename;

	if (redirect_s && *(redirect_s + 1) != '\0' && *(redirect_s + 1) != '>')
	{
		(*index)++;
		filename = ft_strdup(redirect_s + 1);
	}
	else if (tokens[(*index) + 1])
	{
		(*index) += 2;
		filename = ft_strdup(tokens[(*index) - 1]);
	}
	else
	{
		(*index)++;
		return (report_error(ERROR_SYNTAX, "newline"), NULL);
	}
	if (filename)
	{
		cleaned_filename = clean_arg(filename);
		return (free(filename), cleaned_filename);
	}
	return (NULL);
}

t_ast_node	*parse_redirect_node(char **tokens, int *index,
	t_ast_node *cmd_node)
{
	t_node_type	redirect_type;
	t_ast_node	*redirect_node;
	int			fd;
	char		*filename;
	char		*redirect_s;

	redirect_type = get_redirect_type_and_symbol(tokens[*index], &redirect_s);
	fd = parse_redirect_fd(tokens[*index]);
	filename = get_filename(tokens, index, redirect_s);
	if (!filename)
		return (NULL);
	redirect_node = create_node(redirect_type, filename, fd);
	free(filename);
	attach_redirect(cmd_node, redirect_node);
	return (redirect_node);
}
