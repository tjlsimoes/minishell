/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:55:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/18 15:06:16 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home_prev_tilde(char **path)
{
	if (!path)
		return (1);
	if (!(*path))
		return (cd_home(path));
	else if (ft_strncmp((*path), "-", ft_strlen((*path))) == 0)
		return (cd_prev(path));
	else if (ft_strncmp((*path), "~", 1) == 0)
		return (cd_tilde(path));
	return (0);
}

int	cd_special_cases(char **path)
{
	char	cwd[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*env_pair;

	ft_bzero(cwd, PATH_MAX);
	ft_bzero(old_pwd, PATH_MAX);
	getcwd(old_pwd, PATH_MAX);
	if (cd_home_prev_tilde(path))
		return (1);
	if (chdir((*path)) != 0)
		return (chdir_error(path), 1);
	if (getcwd(cwd, PATH_MAX))
	{
		env_pair = ft_strjoin("PWD=", cwd);
		add_env_var(&(get_sh()->env_var), env_pair);
		free(env_pair);
		env_pair = ft_strjoin("OLDPWD=", old_pwd);
		add_env_var(&(get_sh()->env_var), env_pair);
		free(env_pair);
		return (0);
	}
	else
		return (1);
}

int	ft_cd(char **path)
{
	char	cwd[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*env_pair;

	if (ft_strlen((*path)) > PATH_MAX)
		return (report_error(ERROR_SYNTAX, "cd: File name too long"), 1);
	if (!(*path) || ft_strncmp((*path), "-", ft_strlen((*path))) == 0
		|| ft_strncmp((*path), "~", 1) == 0)
		return (cd_special_cases(path));
	ft_bzero(cwd, PATH_MAX);
	ft_bzero(old_pwd, PATH_MAX);
	getcwd(old_pwd, PATH_MAX);
	if (chdir((*path)) != 0)
		return (chdir_error(path), 1);
	if (getcwd(cwd, PATH_MAX))
	{
		env_pair = ft_strjoin("PWD=", cwd);
		add_env_var(&(get_sh()->env_var), env_pair);
		free(env_pair);
		env_pair = ft_strjoin("OLDPWD=", old_pwd);
		add_env_var(&(get_sh()->env_var), env_pair);
		return (free(env_pair), 0);
	}
	else
		return (1);
}
// Note that path is assumed to be heap allocated
// and is not freed on ft_cd.
