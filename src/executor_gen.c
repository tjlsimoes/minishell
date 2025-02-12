/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_gen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:10:40 by tjorge-l          #+#    #+#             */
/*   Updated: 2025/02/12 13:10:56 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**generate_argv(t_ast_node **ast)
{
	int			size;
	char		**argv;
	t_ast_node	*node;

	if (!ast || !(*ast) || !(*ast)->value)
		return (NULL);
	node = *ast;
	size = get_command_size(ast);
	argv = ft_calloc(1, ++size * sizeof(char *));
	if (!argv)
		return (NULL);
	size = 0;
	argv[size++] = ft_strdup(node->value);
	node = node->left;
	while (node)
	{
		argv[size++] = ft_strdup(node->value);
		if (!argv[size - 1])
			return (clear_array_idx(argv, size - 1), NULL);
		node = node->right;
	}
	argv[size] = NULL;
	return (argv);
}
// Note that there's no safeguard for size == 0
//   as that condition is safeguarded by the initial
//   conditional (if (!ast ...))

char	**generate_envp(void)
{
	char		**envp;
	int			size;
	t_list		*env_var;

	env_var = get_sh()->env_var;
	if (!env_var)
		return (NULL);
	size = ft_lstsize(env_var);
	if (size == 0)
		return (NULL);
	envp = (char **)ft_calloc(1, ++size * sizeof(char *));
	if (!envp)
		return (NULL);
	size = 0;
	while (env_var)
	{
		envp[size++] = ft_strdup(env_var->content);
		if (!envp[size - 1])
			return (clear_array_idx(envp, size - 1), NULL);
		env_var = env_var->next;
	}
	envp[size] = NULL;
	return (envp);
}
// Is there a need to safeguard possibility of
//   get_sh() returning NULL?
