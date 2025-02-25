/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:11 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/23 14:34:41 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gen_redirect_out(t_ast_node **current)
{
	int fd_out;

	fd_out = open((*current)->value, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_out == -1)
		return (report_error(ERROR_OPEN, (*current)->value), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	gen_redirect_append(t_ast_node **current)
{
	int	fd_out;

	fd_out = open((*current)->value, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (fd_out == -1)
		return (report_error(ERROR_OPEN, (*current)->value), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_out) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int gen_redirect_stdout(t_ast_node **ast)
{
	t_ast_node	*node;

	node = (*ast)->right;
	while (node)
	{
		if (node->type == NODE_REDIRECT_OUT)
		{
			if (!gen_redirect_out(&node))
				return (0);
		}
		else if (node->type == NODE_REDIRECT_APPEND)
		{
			if (!gen_redirect_append(&node))
				return (0);
		}
		node = node->right;
	}
	return (1);
}

//all redirections should fail immediately on the first error. That will pass TEST 60 now.
int gen_redirect_in(t_ast_node **ast)
{
	t_ast_node	*node;
	int			fd_in;

	node = (*ast)->right;
	while (node)
	{
		if (node->type == NODE_REDIRECT_IN)
		{
			fd_in = open(node->value, O_RDONLY);
			if (fd_in == -1)
				return (report_error(ERROR_OPEN, node->value), 0);
			if (dup2(fd_in, STDIN_FILENO) == -1)
				return (close(fd_in), report_error(ERROR_DUP2, node->value), 0);
			if (close(fd_in) == -1)
				return (report_error(ERROR_CLOSE, node->value), 0);
		}
		node = node->right;
	}
	return (1);
}

void	heredoc_read(t_ast_node **heredoc_node, char **line, int fd[2])
{
	t_ast_node	*heredoc;

	if (!heredoc_node || !(*heredoc_node || !line || !(*line)))
		return ;
	heredoc = *heredoc_node;
	(*line) = alt_gnl(0, NULL);
	while ((*line))
	{
		if (ft_strncmp((*line), heredoc->value, ft_strlen(heredoc->value)) == 0
			&& (*line)[ft_strlen(heredoc->value)] == '\n')
			break;
		if (heredoc->quote_char == 'N')
			expand_env_var(line);
		write(fd[1], (*line), ft_strlen((*line)));
		free((*line));
		(*line) = NULL;
		(*line) = alt_gnl(0, heredoc->value);
	}
	free((*line));
}

int	gen_heredoc(t_ast_node **ast)
{
	t_ast_node	*heredoc;
	int			fd[2];
	char		*line;

	heredoc = get_heredoc(ast);
	if (!heredoc)
		return (1);
	if (pipe(fd) == -1)
		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
	heredoc_read(&heredoc, &line, fd);
	if (close(fd[1]) == -1)
		return (report_error(ERROR_CLOSE, "pipe write end"), 0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]), report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0); // Possible error message needed: errno.
	if (close(fd[0]) == -1)
		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
	return (1);
}
// Assuming value of heredoc is the delimiter.
