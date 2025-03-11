/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_res_utils_b.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:43:54 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/03/11 14:59:33 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	minishell_check(t_ast_node **ast, char *abs_path)
{
	char	**split;
	int		i;

	if (ft_strncmp((*ast)->value, "minishell", ft_strlen("minishell") == 0))
		return (true);
	else if (ft_strncmp((*ast)->value, "./minishell",
			ft_strlen((*ast)->value)) == 0)
		return (true);
	i = 0;
	split = ft_split(abs_path, '/');
	if (!split)
		return (false);
	while (split[i])
		i++;
	if (ft_strncmp(split[--i], "minishell", ft_strlen((*ast)->value)) == 0)
		return (clear_array(split), true);
	return (false);
}

void	update_shlvl_free(char *env_value, char *updated_shlvl)
{
	free(env_value);
	free(updated_shlvl);
}

void	update_shlvl(char **envp)
{
	int		i;
	char	*env_value;
	char	*env_shlvl;
	char	*updated_shlvl;

	i = -1;
	env_value = get_env_value(
			get_env_pair((&get_sh()->env_var), "SHLVL"));
	updated_shlvl = ft_itoa(ft_atoi(env_value) + 1);
	env_shlvl = ft_strjoin("SHLVL=", updated_shlvl);
	if (!env_shlvl)
	{
		update_shlvl_free(env_value, updated_shlvl);
		return ;
	}
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			free(envp[i]);
			envp[i] = env_shlvl;
		}
	}
	update_shlvl_free(env_value, updated_shlvl);
}
