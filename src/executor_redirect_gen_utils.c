/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirect_gen_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:03:00 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/18 11:09:52 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alt_gnl(int fd, char *delimiter)
{
	char		*line;
	static char	*leftover[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	leftover[fd] = ft_read_to_leftover(fd, leftover[fd]);
	if (!leftover[fd])
		return (NULL);
	line = ft_get_line(leftover[fd]);
	if (!line)
	{
		free(leftover[fd]);
		leftover[fd] = NULL;
		return (NULL);
	}
	if (delimiter && ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& line[ft_strlen(delimiter)] == '\n')
		{
			free(leftover[fd]);
			leftover[fd] = NULL;
			return (free(line), NULL);
		}
	else
		leftover[fd] = ft_new_leftover(leftover[fd]);
	return (line);
}

// Remove leading tab characters.
// Returns 1 if successful.
// Returns 0 if an error occurs.
int	rm_tab_trail(char **str)
{
	int		i;
	char	*result;

	if (!str || !(*str))
		return (0);
	i = 0;
	while ((*str)[i] == '\t')
		i++;
	if (i == 0)
		return (1);
	result = ft_strdup(&(*str)[i]);
	if (!result)
		return (0);
	free(*str);
	*str = NULL;
	*str = result;
	return (1);
}
