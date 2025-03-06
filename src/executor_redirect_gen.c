/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:11 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/05 17:47:10 by tjorge-l         ###   ########.fr       */
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

int	gen_redirect_in(t_ast_node **current)
{
	int	fd_in;

	fd_in = open((*current)->value, O_RDONLY);
	if (fd_in == -1)
		return (report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*current)->value), 0);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_in) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

int	gen_heredoc(t_ast_node **ast)
{
	int			fd[2];
	char		*line;

	if (!ast || !(*ast))
		return (0);
	if (pipe(fd) == -1)
		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
	heredoc_read(ast, &line, fd);
	if (close(fd[1]) == -1)
		return (report_error(ERROR_CLOSE, "pipe write end"), 0);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]), report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0); // Possible error message needed: errno.
	if (close(fd[0]) == -1)
		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
	return (1);
}

int	gen_redirections(t_ast_node **ast)
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
		else if (node->type == NODE_REDIRECT_IN)
		{
			if (!gen_redirect_in(&node))
				return (0);
		}
		else if (node->type == NODE_HEREDOC)
		{
			if (!gen_heredoc(&node))
				return (0);
		}
		node = node->right;
	}
	return (1);
}

// void	error_gen_red_in(int last_fd, t_ast_node **ast)
// {
// 	if (last_fd != -1)
// 		close(last_fd);
// 	get_sh()->exit_status = 1;
// 	set_exit_status(-1, false);
// 	report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*ast)->value);
// }

// //all redirections should fail immediately on the first error. That will pass TEST 60 now.
// int		gen_redirect_in(t_ast_node **ast)
// {
// 	t_ast_node	*node;
// 	int			fd_in;
// 	int			last_valid_fd;

// 	node = (*ast)->right;
// 	last_valid_fd = -1;
// 	while (node)
// 	{
// 		if (node->type == NODE_REDIRECT_IN)
// 		{
// 			fd_in = open(node->value, O_RDONLY);
// 			if (fd_in == -1)
// 				return (error_gen_red_in(last_valid_fd, &node), 0);
// 			if (last_valid_fd != -1)
// 				close(last_valid_fd);
// 			last_valid_fd = fd_in;
// 		}
// 		node = node->right;
// 	}
// 	if (last_valid_fd != -1)
// 	{
// 		dup2(last_valid_fd, STDIN_FILENO);
// 		close(last_valid_fd);
// 	}
// 	return (1);
// }

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
