/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:43:02 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/05 16:17:13 by tjorge-l         ###   ########.fr       */
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

void	parse_env_variable(char **tokens, int *index, t_ASTNode *cmd_node)
{
	t_ASTNode	*arg_node;

	expand_env_variable(&(tokens[*index]));
	arg_node = create_node(NODE_ARGUMENT, tokens[*index], -1);
	(*index)++;
	attach_node(cmd_node, arg_node);
}
