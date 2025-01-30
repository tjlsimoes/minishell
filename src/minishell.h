/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:32 by asafrono          #+#    #+#             */
/*   Updated: 2025/01/30 13:10:27 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/src/libft.h"
# include "../libft/src/ft_printf/ft_printf.h"
# include "../libft/src/get_next_line/get_next_line_bonus.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define MAX_INPUT_LENGTH 1024

typedef enum e_ErrorType
{
	ERROR_UNCLOSED_QUOTE,
	ERROR_SYNTAX
}	t_ErrorType;

typedef enum e_NodeType
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	NODE_ENV_VAR,
	NODE_HEREDOC
}	t_NodeType;

typedef struct s_ASTNode
{
	t_NodeType			type;
	char				*value;
	int					fd; // NEW FIELD
	struct s_ASTNode	*left;
	struct s_ASTNode	*right;
}	t_ASTNode;

typedef struct s_token_info
{
	char	**tokens;
	int		index;
	char	*current_token;
	int		token_length;
	char	quote_char;
}	t_token_info;

// Exit Status Exploration
typedef struct s_minishell
{
	int		exit_status;
	t_list	*env_var;
}	t_minishell;

t_minishell		*get_minishell(void);
void			do_something(void);
void			set_exit_status(int	wstatus);

// Environment Exploration
char			*get_non_var(char *str);
char			*strs_join(char **array);
void			*clear_array(char **array);
char			*expand_env_vars(char *str, t_list **env_vars);
char			**env_vars_expansion(char *str, t_list **env_vars);

void			print_env_vars(t_list **lst);
char			*get_env_pair(t_list **env_vars, char *key);
char			*get_env_key(char *pair);
char			*get_env_value(char *pair);
int				update_env_var(t_list **lst, char *content);

void			add_env_var(t_list **lst, char *content);
void			del_env_var(t_list **lst, char *content);
int				is_key(t_list *env_var, char *str);

void			ft_lstdel(t_list **lst);
int				idx(char *str, char c);
void			free_node(t_list **node_adrr);
int				special_chars(char c);
char			*alt_strjoin(char *s1, char *s2);
int				ft_strcpy(char *str, char *s, int start);

// Function prototypes
//ast.c
t_ASTNode	*create_node(t_NodeType type, char *value, int fd);
void		print_ast(t_ASTNode *node, int depth);
void		free_ast(t_ASTNode *node);
//parser
t_ASTNode	*parse_command(char **tokens, int *index);
t_ASTNode	*parse_redirect(char **tokens, int *index);
void		parse_redirect_node(char **tokens, int *index, t_ASTNode *cmd_node);
t_ASTNode	*parse_pipe(char **tokens, int *index);
t_ASTNode	*handle_pipe(t_ASTNode *root, t_ASTNode *node);
t_ASTNode	*parse(char **tokens);
//tokenizer
int			process_input(const char *input, t_token_info *info);
char		**tokenize_input(const char *input);
//utils
int			is_redirect(char *token);
void		print_indent(int indent);
void		print_node(const t_ASTNode *node, int indent);
void		pretty_print_ast(const t_ASTNode *node, int indent);

void		display_history();
void		process_tokens(char *input);
void 		report_error(t_ErrorType error_type, char *details);
void		free_tokens(char **tokens);

#endif
