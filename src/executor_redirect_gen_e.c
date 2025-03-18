/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen_e.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:41:07 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/29 12:41:34 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns allocated string with file path for a temporary
//   file with the lowest index in the pattern:
//   /tmp/temp_file-x
char	*get_tempfile_name(void)
{
	char	*temp_file;
	char	*base;
	int		i;
	char	*nbr;

	if (access("/tmp/temp_file-0", F_OK) != 0)
		return (ft_strdup("/tmp/temp_file-0"));
	base = ft_strdup("/tmp/temp_file-");
	if (!base)
		return (NULL);
	i = 1;
	while (1)
	{
		nbr = ft_itoa(i);
		if (!nbr)
			return (free(base), NULL);
		temp_file = ft_strjoin("/tmp/temp_file-", nbr);
		if (!temp_file)
			return (free(nbr), free(base), NULL);
		if (access(temp_file, F_OK) != 0)
			return (free(nbr), free(base), temp_file);
		free(nbr);
		free(temp_file);
		i++;
	}
}

int	new_heredoc_read_aux(char *file_path)
{
	int	temp_file_fd;

	setup_heredoc_signals();
	temp_file_fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (temp_file_fd == -1)
		return (report_error(ERROR_OPEN, "heredoc write file descriptor"), -1);
	get_sigfree()->red[0] = temp_file_fd;
	return (temp_file_fd);
}
