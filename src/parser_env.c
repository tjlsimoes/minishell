/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:43:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/22 13:53:09 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env_variable(char **token)
{
	char		*var_value;
	char		*key;
	char		*not_name;
	t_minishell	*minishell;

	minishell = get_sh();
	if (ft_strncmp(*token, "$?", 3) == 0)
	{
		free(*token);
		*token = ft_itoa(minishell->exit_status);
		return ;
	}
	not_name = get_non_var(*token + 1);
	if (not_name)
	{
		key = ft_calloc(1, not_name - *token);
		ft_strlcpy(key, *token + 1, not_name - *token);
		not_name = ft_strdup(not_name);
	}
	else
		key = ft_strdup(*token + 1);
	free(*token);
	*token = NULL;
	var_value = get_env_value(get_env_pair(&(get_sh()->env_var), key));
	if (not_name)
	{
		*token = alt_strjoin(var_value, not_name);
		free(not_name);
	}
	else
		*token = var_value;
	free(key);
}

// Note that in case of not_name != NULL, var_value will be freed
// from within alt_strjoin.

t_ast_node	*parse_env_variable(char **tokens, int *index)
{
	char		*expanded;
	t_node_type	node_type;

	expand_env_var(&(tokens[*index]));
	expanded = tokens[*index];
	if (*index == 0)
		node_type = NODE_COMMAND;
	else
		node_type = NODE_ARGUMENT;
	(*index)++;
	return (create_node(node_type, expanded, -1));
}
