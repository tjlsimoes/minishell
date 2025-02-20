/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:32 by asafrono          #+#    #+#             */
/*   Updated: 2025/02/19 14:06:27 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
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
# include <sys/stat.h>
# include <errno.h>

# define MAX_INPUT_LENGTH 1024

typedef enum e_error
{
	ERROR_UNCLOSED_QUOTE,
	ERROR_SYNTAX
}	t_error;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_APPEND,
	NODE_ENV_VAR,
	NODE_HEREDOC
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				*value;
	int					fd;
	char                quote_char;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

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
	char		*input;
	t_list		*env_var;
	char		**tokens;
	t_ast_node	*ast;
	int			exit_status;
}	t_minishell;

t_minishell		*get_sh(void);
void			init_minishell(char **envp);
void			do_something(void);
void			set_exit_status(int wstatus);

// Environment Exploration
char			*get_non_var(char *str);
char			*strs_join(char **array);
void			*clear_array(char **array);

void			print_env_vars(t_list **lst);
char			*get_env_pair(t_list **env_vars, char *key);
char			*get_env_key(char *pair);
char			*alt_get_env_key(char *pair);
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

int				get_quote(char **str, char *quote);
void			remove_quotes(char **str);
int				valid_env_char(char c);
int				env_var_idx(char *str);
char			*get_env_var(char **orig, char **non_var, int env_idx);

char			*get_pre_env(char **orig, int env_idx);
char			*join_sections(int env_idx, char **str, char **key,
					char **non_var);
void			expand_env_var(char	**str);

// Builtins
int				cd_home_prev_tilde(char **path);
int				cd_special_cases(char **path);
int				ft_cd(char **path);

int				invalid_key(char *key);
void			export_error(char **env_pair);
int				ft_export(char **str);
int				ft_unset(char *env_name);
int				ft_env(t_list **lst);

int				ft_pwd(void);
int				ft_echo(char *str, bool n);

int				cd_path_error(char **path, char *error_msg);
void			chdir_error(char **path);
int				cd_home(char **path);
int				cd_prev(char **path);
int				cd_tilde(char **path);

// Function prototypes
//ast.c
t_ast_node		*create_node(t_node_type type, char *value, int fd);
void			print_ast(t_ast_node *node, int depth);
void			free_ast(t_ast_node *node);
//parser
t_ast_node		*parse_command(char **tokens, int *index);
t_ast_node		*parse_redirect(char **tokens, int *index);
t_ast_node 		*parse_redirect_node(char **tokens, int *index,
					t_ast_node *cmd_node);
t_ast_node		*parse_pipe(char **tokens, int *index);
t_ast_node		*handle_pipe(t_ast_node *root, t_ast_node *node);
t_ast_node		*parse(char **tokens);
t_ast_node		*parse_pipeline(char **tokens, int *index);
void			attach_node(t_ast_node *cmd_node, t_ast_node *new_node);
t_ast_node		*parse_env_variable(char **tokens, int *index);
void			expand_env_variable(char **token);
t_ast_node		*parse_argument_node(char *value, int fd);
//tokenizer
int				process_input(const char *input, t_token_info *info);
char			**tokenize_input(const char *input);
//utils
int				is_redirect(char *token);
void			print_indent(int indent);
void			print_node(const t_ast_node *node, int indent);
void			pretty_print_ast(const t_ast_node *node, int indent);
void			display_history(void);
void			process_tokens(char *input);
void			report_error(t_error error_type, char *details);
void			free_tokens(char **tokens);
char			*expand_within_quotes(char *str);
char			*extract_var_name(char *str);
char			*find_r_symbol(char *token);

// signals
void			handle_sigint(int sig);
void			setup_signals(void);

// Executor
int				ft_cd_exec(t_ast_node **ast);
int				ft_unset_exec(t_ast_node **ast);
int				ft_export_exec(t_ast_node **ast);
void			builtins_switch(t_ast_node **ast);
void			builtins_exec(t_ast_node **ast);
void			exec_switch(t_ast_node **ast);
void			simple_command_exec(t_ast_node **ast);

int				ft_echo_iter(t_ast_node **ast, bool n);
int				ft_echo_exec(t_ast_node **ast);
char			**path_split(void);

void			path_error_f(char *binary);
void			path_error_x(char **abs_path);
void			path_error_env(char *binary);
int				get_command_size(t_ast_node **ast);
void			clear_array_idx(char **array, int idx);

char			**generate_argv(t_ast_node **ast);
char			**generate_envp(void);
int				init_path_vars(char ***split, char *binary, int *i);
char			*path_resolution(char *binary);
void			attempt_path_resolution(t_ast_node **ast);

char			*get_redirect_out(t_ast_node **ast);
char			*get_redirect_in(t_ast_node **ast);
char			*get_append(t_ast_node **ast);
t_ast_node		*get_heredoc(t_ast_node **ast);
int				gen_redirect_out(t_ast_node **ast);
int				gen_redirect_in(t_ast_node **ast);
int				gen_append(t_ast_node **ast);
int				gen_heredoc(t_ast_node **ast);
void			child_exec(char *abs_path, t_ast_node **ast);
void			child_free(char *abs_path);

bool			any(char **array, char *value);
char			*alt_gnl(int fd, char *delimiter);
int				rm_tab_trail(char **str);
int				alt_rm_quotes(char **str);
void			heredoc_read(t_ast_node **heredoc_node, char **line, int fd[2]);
void			rm_quotes_gen_res(char **str, char **result);


void	alt_child_exec(char *abs_path, t_ast_node **ast, int fd_to_close);
void	alt_attempt_path_res(t_ast_node **ast, int fd_to_close);
void	alt_exec_switch(t_ast_node **ast, int fd_to_close);
void	exec_pipe_left(t_ast_node **ast, int fd[2]);
void	exec_pipe_right(t_ast_node **ast, int fd[2]);
void	exec_pipe(t_ast_node **ast, int fd_to_close);

#endif