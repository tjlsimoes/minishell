/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:11 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/03 17:46:11 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gen_redirect_out(t_ast_node **ast)
{
	char	*redirect_out;
	int		fd_out;

	redirect_out = get_redirect_out(ast);
	fd_out = -2;
	if (!redirect_out)
		return (1);
	fd_out = open(redirect_out, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd_out == -1)
		return (report_error(ERROR_OPEN, redirect_out), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0); // Possible error message needed: errno.
	if (close(fd_out) == -1)
		return (report_error(ERROR_CLOSE, redirect_out), 0);
	return (1);
}

// int	gen_redirect_in(t_ast_node **ast)
// {
// 	char	*redirect_in;
// 	int		fd_in;

// 	redirect_in = get_redirect_in(ast);
// 	fd_in = -2;
// 	if (!redirect_in)
// 		return (1);
// 	fd_in = open(redirect_in, O_RDONLY);
// 	if (fd_in == -1)
// 		return (report_error(ERROR_OPEN, redirect_in), 0);
// 	if (dup2(fd_in, STDIN_FILENO) == -1)
// 		return (close(fd_in),report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0); // Possible error message needed: errno.
// 	if (close(fd_in) == -1)
// 		return (report_error(ERROR_CLOSE, redirect_in),0);
// 	return (1);
// }

//all redirections should fail immediately on the first error. That will pass TEST 60 now.
int		gen_redirect_in(t_ast_node **ast)
{
	t_ast_node	*node;
	int			fd_in;
	int			last_valid_fd;

	node = (*ast)->right;
	last_valid_fd = -1;
	while (node)
	{
		if (node->type == NODE_REDIRECT_IN)
		{
			fd_in = open(node->value, O_RDONLY);
			if (fd_in == -1)
				return (report_error(ERROR_NO_SUCH_FILE_OR_DIR, node->value), 0);
			if (last_valid_fd != -1)
				close(last_valid_fd);
			last_valid_fd = fd_in;
		}
		node = node->right;
	}
	if (last_valid_fd != -1)
		dup2(last_valid_fd, STDIN_FILENO);
	return (1);
}

int	gen_append(t_ast_node **ast)
{
	char	*append;
	int		fd_out;

	append = get_append(ast);
	fd_out = -2;
	if (!append)
		return (1);
	fd_out = open(append, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_out == -1)
		return (report_error(ERROR_OPEN, append), 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (close(fd_out), report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0); // Possible error message needed: errno.
	if (close(fd_out) == -1)
		return (report_error(ERROR_CLOSE, append), 0);
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
