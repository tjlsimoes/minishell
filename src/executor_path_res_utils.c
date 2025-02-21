/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:14:20 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/21 19:42:56 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alt_split_print_test(char *s, int b, int e)
{
	int		j;

	j = b;
	printf("Substring: ");
	while (s[j] && j < e)
	{
		printf("%c", s[j]);
		j++;
	}
	printf("\n");
}

char	*get_abs_path(char *path)
{
	char	*temp;
	char	cwd[PATH_MAX];

	if (ft_strncmp(path, ":", 2) == 0)
	{
		ft_bzero(cwd, PATH_MAX);
		if (!getcwd(cwd, PATH_MAX))
			return (NULL);
		temp = ft_strjoin(cwd, "/");
	}
	else
		temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	return (temp);
}
