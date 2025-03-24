/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen_a.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:59:11 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/15 21:14:07 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gen_redirect_out(t_ast_node **current)
{
	int	fd_out;

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

int	gen_redirect_stdout(t_ast_node **ast)
{
	t_ast_node	*node;

	node = (*ast)->right;
	while (node)
	{
		if ((node->type == NODE_REDIRECT_OUT && !gen_redirect_out(&node))
			|| (node->type == NODE_REDIRECT_APPEND
				&& !gen_redirect_append(&node)))
			return (0);
		node = node->right;
	}
	return (1);
}

int	gen_redirect_in(t_ast_node **current, int stdins)
{
	int	fd_in;

	fd_in = open((*current)->value, O_RDONLY);
	if (fd_in == -1)
		return (report_error(ERROR_NO_SUCH_FILE_OR_DIR, (*current)->value), 0);
	if (stdins != 0)
		return (close(fd_in), 1);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(fd_in), report_error(ERROR_DUP2, (*current)->value), 0);
	if (close(fd_in) == -1)
		return (report_error(ERROR_CLOSE, (*current)->value), 0);
	return (1);
}

// int	gen_heredoc(t_ast_node **ast, int stdins_rem)
// {
// 	int	fd[2];
// 	int	orig[2];

// 	if (pipe(fd) == -1)
// 		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
// 	orig[0] = dup(STDIN_FILENO);
// 	orig[1] = dup(STDOUT_FILENO);
// 	heredoc_read(ast, fd[1]);
// 	close(fd[1]);
// 	dup2(orig[1], STDOUT_FILENO);
// 	close(orig[0]);
// 	close(orig[1]);
// 	if (stdins_rem == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 	}
// 	else
// 		close(fd[0]);
// 	return (1);
// }

// -------------------------------------------------------------------------
// int	gen_heredoc(t_ast_node **ast, int stdins_rem)
// {
// 	int		fd[2];
// 	char	*line;

// 	if (!ast || !*ast)
// 		return (0);
// 	if (stdins_rem != 0)
// 	{
// 		heredoc_read(ast, &line, STDIN_FILENO, stdins_rem);
// 		return (1);
// 	}
// 	if (pipe(fd) == -1)
// 		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
// 	heredoc_read(ast, &line, fd[1], stdins_rem);
// 	if (close(fd[1]) == -1)
// 		return (close(fd[0]), report_error(ERROR_CLOSE, "pipe write end"), 0);
// 	if (dup2(fd[0], STDIN_FILENO) == -1)
// 		return (close(fd[0]),
// 			report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0);
// 	if (close(fd[0]) == -1)
// 		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
// 	return (1);
// }

// int	gen_heredoc(t_ast_node **ast, int stdins_rem)
// {
// 	int			fd[2];
// 	int			temp_file;

// 	setup_child_signals();
// 	if (!ast || !(*ast))
// 		return (0);
// 	if (stdins_rem != 0)
// 	{
// 		heredoc_read(ast, -1, stdins_rem);
// 		return (1);
// 	}
// 	if (pipe(fd) == -1)
// 		return (report_error(ERROR_PIPE, "Failed to create pipe"), 0);
// 	get_sigfree()->red[0] = fd[0];
// 	get_sigfree()->red[1] = fd[1];
// 	heredoc_read(ast, fd[1], stdins_rem);
// 	if (get_sigfree()->interrupted)
// 	{
// 		close(fd[1]);
// 		close(fd[0]);
// 		return (0);
// 	}
// 	if (close(fd[1]) == -1)
// 		return (close(fd[0]), report_error(ERROR_CLOSE, "pipe write end"), 0);
// 	temp_file = open("/home/pgr/repos/42/minishell/temp_file", O_CREAT | O_RDONLY);
// 	if (dup2(temp_file, STDIN_FILENO) == -1)
// 		return (close(fd[0]),
// 			report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0);
// 	if (close(fd[0]) == -1)
// 		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
// 	if (close(temp_file) == -1)
// 		return (report_error(ERROR_CLOSE, "pipe read end"), 0);
// 	get_sigfree()->red[0] = -1;
// 	get_sigfree()->red[1] = -1;
// 	return (1);
// }



int	gen_heredoc(t_ast_node **ast, int stdins_rem)
{
	// int			tempfile_w;
	// int			tempfile_r;
	int			temp_file;

	setup_child_signals();
	if (!ast || !(*ast))
		return (0);
	if (stdins_rem != 0)
	{
		heredoc_read(ast, -1, stdins_rem);
		return (1);
	}
	temp_file = open("/home/pgr/repos/42/minishell/temp_file",  O_CREAT | O_WRONLY | O_TRUNC, 0777);

	if (temp_file == -1)
		ft_putstr_fd("Invalid temp_file_w\n", 2);
	// Need to safeguard possibility of -1 return
	
	heredoc_read(ast, temp_file, stdins_rem);
	
	close(temp_file);

	temp_file = open("/home/pgr/repos/42/minishell/temp_file", O_RDONLY);
	// Need to close fd in case of error in the below returns.
	if (temp_file == -1)
		ft_putstr_fd("Invalid tempfile_r\n", 2);

	if (get_sigfree()->interrupted)
		return (0);
	if (get_sh()->close_stdin == true && dup2(temp_file, STDIN_FILENO) == -1)
		return (0); //
	close(temp_file);
	get_sigfree()->red[0] = -1;
	get_sigfree()->red[1] = -1;
	unlink("/home/pgr/repos/42/minishell/temp_file");
	return (1);
}







// int gen_heredoc(t_ast_node **ast, int stdins_rem)
// {
//     int fd;
//     char tmp_filename[] = "/tmp/minishell_heredocXXXXXX";

//     fd = mkstemp(tmp_filename);
//     if (fd == -1)
//         return (report_error(ERROR_OPEN, "Failed to create temp file for heredoc"), 0);
    
//     unlink(tmp_filename); // Ensure file is deleted after close

//     setup_child_signals();
//     if (!ast || !(*ast))
//         return (0);
    
//     heredoc_read(ast, fd, stdins_rem);
//     close(fd);

//     // Redirect stdin to this file during execution
//     fd = open(tmp_filename, O_RDONLY);
//     if (fd == -1)
//         return (report_error(ERROR_OPEN, "Failed to reopen temp file for reading"), 0);

//     if (dup2(fd, STDIN_FILENO) == -1)
//         return (close(fd), report_error(ERROR_DUP2, "Failed to duplicate file descriptor"), 0);
    
//     close(fd);
//     return (1);
// }


