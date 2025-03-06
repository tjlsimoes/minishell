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

int	init_path_vars(char ***split, char *binary)
{
	if (!binary)
		return (0);
	else if (path_check_abs(binary))
		return (2);
	else if (path_check_pwd(binary))
		return (3);
	else if (path_check_rel(binary))
		return (4);
	*split = path_split();
	if (!split)
		return (report_error(ERROR_NO_SUCH_FILE_OR_DIR, binary), 0);
	return (1);
}

char	*path_res_iter(char ***split, char *binary)
{
	int		i;
	char	*abs_path;

	i = 0;
	while ((*split)[i])
	{
		abs_path = ft_strjoin((*split)[i], binary);
		if (!abs_path)
			break ;
		if (access(abs_path, F_OK) == 0)
		{
			if (access(abs_path, X_OK) == 0)
				return (clear_array((*split)), abs_path);
			else
				return (report_error(ERROR_PERMISSION_DENIED, abs_path),
					free(abs_path), def_exit(126), clear_array((*split)), NULL);
		}
		free(abs_path);
		i++;
	}
	clear_array((*split));
	report_error(ERROR_COMMAND_NOT_FOUND, binary);
	def_exit(127);
	return (NULL);
}
