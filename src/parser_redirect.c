/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:15:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 12:58:37 by asafrono         ###   ########.fr       */
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

static t_NodeType	get_redirect_type(char *token)
{
	int	i;

	i = 0;
	while (ft_isdigit(token[i]))
		i++;
	if (ft_strncmp(token + i, ">>", 2) == 0)
		return (NODE_REDIRECT_APPEND);
	if (ft_strncmp(token + i, "<<", 2) == 0)
		return (NODE_HEREDOC);
	if (ft_strncmp(token + i, "<", 1) == 0)
		return (NODE_REDIRECT_IN);
	return (NODE_REDIRECT_OUT);
}

static void	attach_redirect(t_ASTNode *cmd_node, t_ASTNode *redirect_node)
{
	t_ASTNode	*current;

	if (cmd_node->right == NULL)
		cmd_node->right = redirect_node;
	else
	{
		current = cmd_node->right;
		while (current->right != NULL)
			current = current->right;
		current->right = redirect_node;
	}
}

void	parse_redirect_node(char **tokens, int *index, t_ASTNode *cmd_node)
{
	t_NodeType	redirect_type;
	t_ASTNode	*redirect_node;
	int			fd;

	if (!tokens[++(*index)])
		return(report_error(ERROR_SYNTAX, "newline"));
	redirect_type = get_redirect_type(tokens[*index]);
	fd = parse_redirect_fd(tokens[*index]);
	redirect_node = create_node(redirect_type, tokens[*index + 1], fd);
	(*index) += 2;
	attach_redirect(cmd_node, redirect_node);
}