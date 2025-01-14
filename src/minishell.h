/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:32 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/14 14:20:57 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/src/libft.h"
# include "../libft/src/get_next_line/get_next_line_bonus.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define MAX_INPUT_LENGTH 1024

typedef enum e_NodeType
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND
}	t_NodeType;

typedef struct s_ASTNode
{
	t_NodeType			type;
	char				*value;
	struct s_ASTNode	*left;
	struct s_ASTNode	*right;
}	t_ASTNode;

typedef struct s_token_info
{
	char	**tokens;
	int		index;
	char	*current_token;
	int		token_length;
}	t_token_info;

// Function prototypes
//ast.c
t_ASTNode	*create_node(t_NodeType type, char *value);
void		print_ast(t_ASTNode *node, int depth);
void		free_ast(t_ASTNode *node);
//parser
t_ASTNode	*parse_command(char **tokens, int *index);
t_ASTNode	*parse_redirect(char **tokens, int *index);
t_ASTNode	*parse_pipe(char **tokens, int *index);
t_ASTNode	*handle_pipe(t_ASTNode *root, t_ASTNode *node);
t_ASTNode	*parse(char **tokens);
//tokenizer
void		process_input(const char *input, t_token_info *info);
char		**tokenize_input(const char *input);
//utils
int			is_redirect(char *token);

#endif
