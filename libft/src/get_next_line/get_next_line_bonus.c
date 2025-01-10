/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:13:02 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/18 13:14:33 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
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
		free (leftover[fd]);
		leftover[fd] = NULL;
		return (NULL);
	}
	leftover[fd] = ft_new_leftover(leftover[fd]);
	return (line);
}

// # include <fcntl.h>
// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*line1;
// 	char	*line2;
// 	int		line_count;

// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1)
// 	{
// 		printf("Error opening file\n");
// 		return (1);
// 	}
// 	line_count = 1;
// 	while (1)
// 	{
// 		line1 = get_next_line(fd1);
// 		line2 = get_next_line(fd2);
// 		if (line1)
// 		{
// 			printf("File 1, line %d: %s\n", line_count, line1);
// 			free(line1);
// 		}
// 		if (line2)
// 		{
// 			printf("File 2, line %d: %s\n", line_count, line2);
// 			free(line2);
// 		}
// 		if (!line1 && !line2)
// 			break ;
// 		line_count++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }
// cc -Wall -Wextra -Werror get_next_line_bonus.c
// get_next_line_utils_bonus.c -o gnl_test && ./gnl_test
