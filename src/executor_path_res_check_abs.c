/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res_check_abs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:05:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/13 23:06:04 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*check_absolute_path(char *binary)
// {
// 	char		*last_slash = strrchr(binary, '/');
// 	char		*parent_path;
// 	struct stat	st;

// 	if (last_slash)
// 	{
// 		parent_path = ft_strdup(binary);
// 		if (parent_path)
// 			parent_path[last_slash - binary] = '\0';
// 	}
// 	else
// 		parent_path = ft_strdup(".");
// 	if (!parent_path)
// 		return (def_exit(1), NULL);
// 	if (stat(parent_path, &st) == 0)
// 		if (!S_ISDIR(st.st_mode))
// 			return (report_error(ERROR_NOT_A_DIRECTORY, parent_path),
//				free(parent_path), def_exit(126), NULL);
// 	free(parent_path);
// 	if (access(binary, F_OK) == 0) {
// 		if (access(binary, X_OK) == 0)
// 			return ft_strdup(binary);
// 		else
// 			return (report_error(ERROR_PERMISSION_DENIED, binary),
//				def_exit(126), NULL);
// 	}
// 	return(report_error(ERROR_NO_SUCH_FILE_OR_DIR, binary),
// 		def_exit(127), NULL);
// }

static char	*find_last_slash(char *str)
{
	char	*last_slash;

	last_slash = NULL;
	while (*str)
	{
		if (*str == '/')
			last_slash = str;
		str++;
	}
	return (last_slash);
}

static char	*get_parent_path(char *binary)
{
	char	*last_slash;
	char	*parent_path;

	last_slash = find_last_slash(binary);
	if (last_slash)
	{
		parent_path = ft_strdup(binary);
		if (parent_path)
			parent_path[last_slash - binary] = '\0';
	}
	else
		parent_path = ft_strdup(".");
	return (parent_path);
}

static int	check_parent_directory(char *parent_path)
{
	struct stat	st;

	if (stat(parent_path, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		report_error(ERROR_NOT_A_DIRECTORY, parent_path);
		free(parent_path);
		def_exit(126);
		return (0);
	}
	return (1);
}

char	*check_absolute_path(char *binary)
{
	char	*parent_path;

	parent_path = get_parent_path(binary);
	if (!parent_path)
		return (def_exit(1), NULL);
	if (!check_parent_directory(parent_path))
		return (NULL);
	free(parent_path);
	if (access(binary, F_OK) == 0)
	{
		if (access(binary, X_OK) == 0)
			return (ft_strdup(binary));
		report_error(ERROR_PERMISSION_DENIED, binary);
		def_exit(126);
		return (NULL);
	}
	report_error(ERROR_NO_SUCH_FILE_OR_DIR, binary);
	def_exit(127);
	return (NULL);
}
