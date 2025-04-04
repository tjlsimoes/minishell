/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:43:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/15 18:41:34 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_key_and_not_name(char **token, char **not_name)
{
	char	*key;

	*not_name = get_non_var(*token + 1);
	if (*not_name)
	{
		key = ft_calloc(1, *not_name - *token);
		ft_strlcpy(key, *token + 1, *not_name - *token);
		*not_name = ft_strdup(*not_name);
	}
	else
		key = ft_strdup(*token + 1);
	return (key);
}

static void	handle_variable_replacement(char **token,
				char *var_value, char *not_name)
{
	if (not_name)
	{
		*token = alt_strjoin(var_value, not_name);
		free(not_name);
		free(var_value);
	}
	else
		*token = var_value;
}

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
	key = extract_key_and_not_name(token, &not_name);
	free(*token);
	var_value = get_env_value(get_env_pair(&(get_sh()->env_var), key));
	if (var_value == NULL)
		var_value = ft_strdup("");
	handle_variable_replacement(token, var_value, not_name);
	free(key);
}

// Note that in case of not_name != NULL, var_value will be freed
// from within alt_strjoin.

t_ast_node	*parse_env_variable(char **tokens, int *index)
{
	char		*expanded;
	t_ast_node	*new_node;

	expand_env_var(&(tokens[*index]));
	expanded = tokens[*index];
	if (*index == 0 && expanded[0] != '\0')
		new_node = env_node_command(expanded);
	else
		new_node = create_node(NODE_ARGUMENT, expanded, -1);
	(*index)++;
	return (new_node);
}
