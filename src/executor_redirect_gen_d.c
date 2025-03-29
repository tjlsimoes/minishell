/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen_d.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:26:19 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/29 12:41:24 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_heredoc_read(t_ast_node **heredoc_node, char *file_path)
{
	t_ast_node	*heredoc;
	char		*line;
	int			temp_file_fd;

	temp_file_fd = new_heredoc_read_aux(file_path);
	heredoc = *heredoc_node;
	line = NULL;
	line = readline("> ");
	while (line && get_sigfree()->interrupted == 0)
	{
		if ((ft_strncmp(line, heredoc->value, ft_strlen(heredoc->value)) == 0
				&& line[ft_strlen(heredoc->value)] == '\0')
			|| get_sigfree()->interrupted != 0)
			break ;
		if (heredoc->quote_char != '\'')
			expand_env_var(&line);
		write(temp_file_fd, line, ft_strlen(line));
		write(temp_file_fd, "\n", 1);
		free(line);
		line = NULL;
		if (get_sigfree()->interrupted == 0)
			line = readline("> ");
	}
	free(line);
	close(temp_file_fd);
}

char	*pre_exec_heredoc_child(t_ast_node **ast)
{
	pid_t		pid;
	char		*temp_file_path;

	if (!ast || !*ast)
		return (NULL);
	temp_file_path = get_tempfile_name();
	pid = fork();
	if (pid == -1)
		return (report_error(ERROR_FORK, "Failed to fork for heredoc"), NULL);
	if (pid == 0)
	{
		sigfree_init(NULL, true);
		new_heredoc_read(ast, temp_file_path);
		sigfree_erase();
		child_free(temp_file_path);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (temp_file_path);
}

void	pre_exec_heredoc(t_ast_node **ast)
{
	t_ast_node	*node;
	char		*temp;

	node = *ast;
	node = node->right;
	while (node)
	{
		if (node->type == NODE_HEREDOC)
		{
			temp = pre_exec_heredoc_child(&node);
			if (node->value)
				free(node->value);
			node->value = ft_strdup(temp);
			free(temp);
			temp = NULL;
		}
		node = node->right;
	}
}

void	pre_exec_heredocs(t_ast_node **ast)
{
	if ((*ast)->type == NODE_PIPE)
	{
		pre_exec_heredocs(&((*ast)->left));
		pre_exec_heredocs(&((*ast)->right));
	}
	else if ((*ast)->type == NODE_COMMAND)
		pre_exec_heredoc(ast);
}
