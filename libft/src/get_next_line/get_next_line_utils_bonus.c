/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:13:00 by asafrono          #+#    #+#             */
/*   Updated: 2024/11/18 13:14:01 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_and_free(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	result = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!result)
		return (free((char *)s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (free((char *)s1), result);
}

char	*ft_read_to_leftover(int fd, char *leftover)
{
	char	*buffer;
	int		read_bytes;
	int		i;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(leftover), NULL);
	while (1)
	{
		read_bytes = read (fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		leftover = ft_strjoin_and_free(leftover, buffer);
		if (!leftover)
			return (free (buffer), NULL);
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
			break ;
	}
	if (read_bytes == -1)
		return (free (buffer), free(leftover), NULL);
	return (free (buffer), leftover);
}

char	*ft_get_line(char *leftover)
{
	int		i;
	char	*line;

	i = 0;
	if (!leftover || !leftover[0])
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_new_leftover(char *leftover)
{
	int		i;
	int		j;
	char	*new_leftover;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
		return (free (leftover), NULL);
	j = 0;
	while (leftover[i + j])
		j++;
	new_leftover = (char *)malloc(sizeof(char) * (j + 1));
	if (!new_leftover)
		return (free(leftover), NULL);
	i++;
	j = 0;
	while (leftover[i])
		new_leftover[j++] = leftover[i++];
	new_leftover[j] = '\0';
	free (leftover);
	return (new_leftover);
}
