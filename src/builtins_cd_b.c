/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:36:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/09 11:48:32 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_path_error(char **path, char *error_msg)
{
	if (!(*path))
	{
		report_error(ERROR_SYNTAX, error_msg);
		return (1);
	}
	return (0);
}

// void	chdir_error(char **path)
// {
// 	int	error;

// 	error = errno;
// 	ft_putstr_fd("-bash: cd: ", 2);
// 	ft_putstr_fd((*path), 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(strerror(error), 2);
// 	ft_putstr_fd("\n", 2);
// }
// Possibility of errno having changed between
// system calls, safeguarded?

int	cd_home(char **path)
{
	(*path) = get_env_value(get_env_pair(&(get_sh()->env_var), "HOME"));
	if (cd_path_error(path, "cd: HOME not set"))
		return (1);
	return (0);
}

int	cd_prev(char **path)
{
	free((*path));
	(*path) = get_env_value(get_env_pair(&(get_sh()->env_var), "OLDPWD"));
	if (cd_path_error(path, "cd: OLDPWD not set"))
		return (1);
	ft_printf("%s\n", (*path));
	return (0);
}

int	cd_tilde(char **path)
{
	char	*env_value;
	char	*non_tilde;

	env_value = NULL;
	non_tilde = NULL;
	non_tilde = ft_strdup(((*path) + 1));
	free(*path);
	env_value = get_env_value(get_env_pair(&(get_sh()->env_var), "HOME"));
	(*path) = alt_strjoin(env_value, non_tilde);
	free(non_tilde);
	return (0);
}
