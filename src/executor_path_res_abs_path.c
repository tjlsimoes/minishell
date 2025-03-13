/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res_abs_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:15:16 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/24 13:19:15 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	path_check_abs(char *binary)
{
	if (ft_strncmp(binary, "/", 1) == 0)
		return (true);
	return (false);
}

bool	path_check_pwd(char *binary)
{
	if (ft_strncmp(binary, "./", 2) == 0)
		return (true);
	return (false);
}

bool	path_check_rel(char *binary)
{
	if (ft_strncmp(binary, "../", 3) == 0)
		return (true);
	return (false);
}

char	*gen_path_pwd(char *binary)
{
	char	cwd[PATH_MAX];
	char	*abs_path;

	getcwd(cwd, PATH_MAX);
	abs_path = ft_strjoin(cwd, binary + 1);
	if (access(abs_path, F_OK) == 0)
	{
		if (access(abs_path, X_OK) == 0)
			return (abs_path);
		else
			return (report_error(ERROR_PERMISSION_DENIED, abs_path),
				free(abs_path), def_exit(126), NULL);
	}
	report_error(ERROR_COMMAND_NOT_FOUND, binary);
	free(abs_path);
	def_exit(127);
	return (NULL);
}

char	*gen_path_rel(char *binary)
{
	char	cwd[PATH_MAX];
	char	*temp;
	char	*abs_path;

	getcwd(cwd, PATH_MAX);
	temp = ft_strjoin(cwd, "/");
	abs_path = alt_strjoin(temp, binary);
	if (access(abs_path, F_OK) == 0)
	{
		if (access(abs_path, X_OK) == 0)
			return (abs_path);
		else
			return (report_error(ERROR_PERMISSION_DENIED, abs_path),
				free(abs_path), def_exit(126), NULL);
	}
	report_error(ERROR_COMMAND_NOT_FOUND, binary);
	free(abs_path);
	def_exit(127);
	return (NULL);
}
