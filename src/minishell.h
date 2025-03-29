/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:32 by asafrono          #+#    #+#             */
/*   Updated: 2025/03/15 21:02:29 by asafrono         ###   ########.fr       */
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

// # define MAX_INPUT_LENGTH 1024

typedef enum e_error
{
	ERROR_UNCLOSED_QUOTE,
	ERROR_SYNTAX,
	ERROR_EXIT_TOO_MANY_ARGS,
	ERROR_EXIT_NUMERIC_REQUIRED,
	ERROR_INVALID_IDENTIFIER,
	ERROR_ENV_WRITE_FAILED,
	ERROR_CD_TOO_MANY_ARGS,
	ERROR_COMMAND_NOT_FOUND,
	ERROR_PERMISSION_DENIED,
	ERROR_NO_SUCH_FILE_OR_DIR,
	ERROR_DUP2,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_OPEN,
	ERROR_CLOSE,
	ERROR_IS_DIR,
	ERROR_NOT_A_DIRECTORY,
	ERROR_MEMORY_ALLOCATION,
	ERROR_NOT_EXECUTABLE
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
	char				quote_char;
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
	char					*input;
	t_list					*env_var;
	char					**tokens;
	t_ast_node				*ast;
	volatile sig_atomic_t	exit_status;
	bool					gen_output;
	bool					close_stdin;
}	t_minishell;

typedef struct s_signal_free
{
	char					*abs_path;
	int						red[2];
	int						orig[2];
	bool					child;
	volatile sig_atomic_t	interrupted;
}	t_signal_free;

// Functions from src/ast.c
t_ast_node		*create_node(t_node_type type, char *value, int fd);
void			free_ast(t_ast_node *node);
void			print_indent(int indent);
void			print_node(const t_ast_node *node, int indent);
void			pretty_print_ast(const t_ast_node *node, int indent);

// Functions from src/builtins_cd_a.c
int				cd_home_prev_tilde(char **path);
int				cd_special_cases(char **path);
int				ft_cd(char **path);

// Functions from src/builtins_cd_b.c
int				cd_path_error(char **path, char *error_msg);
int				cd_home(char **path);
int				cd_prev(char **path);
int				cd_tilde(char **path);

// Functions from src/builtins_env.c
int				invalid_key(char *key);
int				ft_export(char **str);
int				ft_unset(char *env_name);
int				ft_env(t_list **lst);

// Functions from src/builtins_env_utils.c
int				ft_export_noargs(t_list **lst);
int				print_declare(t_list **node);
int				env_write_error(int fd, char *str);

// Functions from src/builtins_exit.c
void			exit_shell(int exit_code, int orig_stdin, int orig_stdout);
int				ft_exit_exec(t_ast_node *args, int orig_stdin, int orig_stdout);

// Functions from src/builtins_pwd_echo.c
int				ft_pwd(void);
int				ft_echo(char *str, bool n);

// Functions from src/env_vars_change.c
void			add_env_var(t_list **lst, char *content);
void			del_env_var(t_list **lst, char *content);
int				update_env_var(t_list **lst, char *content);

// Functions from src/env_vars_expand.c
void			expand_env_var(char	**str);

// Functions from src/env_vars_get_a.c
char			*get_non_var(char *str);
char			*get_env_pair(t_list **env_vars, char *key);
char			*get_env_key(char *pair);
char			*alt_get_env_key(char *pair);
char			*get_env_value(char *pair);

// Functions from src/env_vars_get_b.c
char			*get_pre_env(char **orig, int env_idx);
char			*get_env_var(char **orig, char **non_var, int env_idx);

// Functions from src/env_vars_print.c
void			print_env_vars(t_list **lst);

// Functions from src/env_vars_utils_a.c
char			*strs_join(char **array);
void			*clear_array(char **array);
int				special_chars(char c);
void			ft_lstdel(t_list **lst);

// Functions from src/env_vars_utils_b.c
int				idx(char *str, char c);
void			free_node(t_list **node_adrr);
char			*alt_strjoin(char *s1, char *s2);
int				ft_strcpy(char *str, char *s, int start);
int				is_key(t_list *env_var, char *str);

// Functions from src/env_vars_utils_c.c
int				get_quote(char **str, char *quote);
void			remove_quotes(char **str);
int				valid_env_char(char c);
int				env_var_idx(char *str);
char			*join_sections(int env_idx, char **str,
					char **key, char **non_var);

// Functions from src/error_handling.c
void			report_error(t_error error_type, char *details);
void			chdir_error(char **path);
void			def_exit(int exit_nbr);

// Functions from src/executor_builtins_a.c
int				ft_cd_exec(t_ast_node **ast);
int				ft_unset_exec(t_ast_node **ast);
int				ft_export_exec(t_ast_node **ast);
int				ft_echo_iter(t_ast_node **ast, bool n);
int				ft_echo_exec(t_ast_node **ast);

// Functions from src/executor_gen.c
char			**generate_argv(t_ast_node **ast);
char			**generate_envp(void);

// Functions from src/executor_main_a.c
void			builtins_switch(t_ast_node **ast,
					int orig_stdin, int orig_stdout);
void			builtins_close_fds(int orig_stdin, int orig_stdout);
void			builtins_exec(t_ast_node **ast);
void			exec_switch(t_ast_node **ast);
void			alt_child_exec(char *abs_path, t_ast_node **ast);

// Functions from src/executor_main_b.c
void			alt_attempt_path_res(t_ast_node **ast);
void			alt_exec_switch(t_ast_node **ast);
void			exec_pipe_child_exit(char *error_msg);
void			exec_pipe_left(t_ast_node **ast, int fd[2]);
void			exec_pipe_right(t_ast_node **ast, int fd[2]);

// Functions from src/executor_main_c.c
bool			has_heredocs(t_ast_node **ast);
void			exec_pipe(t_ast_node **ast);
void			simple_command_exec(t_ast_node **ast);

// Functions from src/executor_path_res_a.c
char			**path_split(void);
char			*path_resolution(char *binary);
void			child_exec(char *abs_path, t_ast_node **ast);
bool			cmd_check(char *abs_path);

// Functions from src/executor_path_res_abs_path.c
bool			path_check_abs(char *binary);
bool			path_check_pwd(char *binary);
bool			path_check_rel(char *binary);
char			*gen_path_pwd(char *binary);
char			*gen_path_rel(char *binary);

// Functions from src/executor_path_res_b.c
void			attempt_path_resolution(t_ast_node **ast);

// Functions from src/executor_path_res_check_abs.c
char			*check_absolute_path(char *binary);

// Functions from src/executor_path_res_split.c
int				split_find_end(char *s, int start, char c);
int				alt_count_words(char *s, char c);
char			*alt_get_next_word(char **s, char c);
int				init_get_path_split(int *words, char ***result,
					char *s, char c);
char			**get_path_split(char *s, char c);

// Functions from src/executor_path_res_utils_a.c
void			alt_split_print_test(char *s, int b, int e);
char			*get_abs_path(char *path);
int				init_path_vars(char ***split, char *binary);
char			*path_res_iter(char ***split, char *binary);

// Functions from src/executor_path_res_utils_b.c
bool			minishell_check(t_ast_node **ast);
void			update_shlvl_free(char *env_value, char *updated_shlvl);
void			update_shlvl(char **envp);

// Functions from src/executor_redirect_gen_a.c
int				gen_redirect_out(t_ast_node **current);
int				gen_redirect_append(t_ast_node **current);
int				gen_redirect_stdout(t_ast_node **ast);
int				gen_redirect_in(t_ast_node **current, int stdins);

// Functions from src/executor_redirect_gen_b.c
int				gen_redirections(t_ast_node **ast);
int				nbr_stdins(t_ast_node **ast);

// Functions from src/executor_redirect_gen_c.c
void			standalone_red_parent(t_ast_node **ast);
int				standalone_gen_redirections(t_ast_node **ast);
int				mock_redirect_out(t_ast_node **current);
int				mock_redirect_append(t_ast_node **current);
int				mock_redirect_in(t_ast_node **current);

// Functions from src/executor_redirect_gen_d.c
void			new_heredoc_read(t_ast_node **heredoc_node, char *file_path);
char			*pre_exec_heredoc_child(t_ast_node **ast);
void			pre_exec_heredoc(t_ast_node **ast);
void			pre_exec_heredocs(t_ast_node **ast);

// Functions from src/executor_redirect_gen_e.c
char			*get_tempfile_name(void);
int				new_heredoc_read_aux(char *file_path);

// Functions from src/executor_redirect_gen_utils.c
char			*alt_gnl(int fd, char *delimiter);
int				rm_tab_trail(char **str);

// Functions from src/executor_redirect_get.c
char			*get_redirect_out(t_ast_node **ast);
t_ast_node		*get_heredoc(t_ast_node **ast);

// Functions from src/executor_redirect_get_utils.c
int				get_rm_quotes_len(char **str);
void			rm_quotes_gen_res(char **str, char **result);
int				alt_rm_quotes(char **str);

// Functions from src/executor_utils.c
int				get_command_size(t_ast_node **ast);
void			clear_array_idx(char **array, int idx);
bool			any(char **array, char *value);
void			child_free(char *abs_path);
void			treat_echo_str(t_ast_node **ast);

// Functions from src/exit_status.c
void			set_exit_status(int wstatus, bool child_wait);

// Functions from src/main.c
t_minishell		*get_sh(void);
void			init_minishell(char **envp);
int				process_command(char *input);

// Functions from src/parser.c
void			attach_node(t_ast_node *cmd_node, t_ast_node *new_node);
void			process_env_or_argument(t_ast_node *cmd_node,
					char **tokens, int *index, bool *cmd_initialized);
void			process_command_tokens(t_ast_node *cmd_node,
					char **tokens, int *index);
t_ast_node		*parse_command(char **tokens, int *index);
t_ast_node		*parse(char **tokens);

// Functions from src/parser_argument.c
int				find_redirect_index(char *value);
t_ast_node		*parse_argument_node(char *value, int fd);

// Functions from src/parser_env.c
void			expand_env_variable(char **token);
t_ast_node		*parse_env_variable(char **tokens, int *index);

// Functions from src/parser_env_split.c
char			**split_parser_env(char const *s);

// Functions from src/parser_env_utils.c
bool			has_whitespace(char *str);
t_ast_node		*env_node_command(char *expanded);
void			add_arg_nodes(t_ast_node **cmd_node, t_ast_node **new_node);

// Functions from src/parser_pipe.c
t_ast_node		*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_ast_node		*parse_pipeline(char **tokens, int *index);

// Functions from src/parser_redirect_a.c
int				parse_redirect_fd(char *token);
t_node_type		get_redirect_type(char *token, char **symbol_ptr, int *op_len);
char			*get_filename(char **tokens, int *index,
					char *redirect_s, int op_len);
int				get_redirect_metadata(char *token, t_node_type *redirect_type,
					char **redirect_s, int *op_len);
t_ast_node		*create_redirect_ast_node(char **tokens, int *index,
					t_node_type redirect_type, int fd);

// Functions from src/parser_redirect_b.c
t_ast_node		*parse_redirect_node(char **tokens, int *index,
					t_ast_node *cmd_node);

// Functions from src/signals_a.c
void			handle_sigint(int sig);
void			setup_heredoc_signals(void);
void			setup_child_signals(void);
void			setup_signals(void);

// Functions from src/signals_b.c
void			handle_child_sig(int sig);
void			handle_heredoc_sig(int sig);
t_signal_free	*get_sigfree(void);
void			sigfree_init(char *abs_path, bool child);
void			sigfree_erase(void);

// Functions from src/tokenizer.c
void			handle_quote(const char *input, int *i,
					t_token_info *info, bool *in_quote);
void			handle_operator(const char *input, int *i, t_token_info *info);
int				process_input(const char *input, t_token_info *info);
char			**tokenize_input(const char *input);
void			process_tokens(char *input);

// Functions from src/tokenizer_utils.c
bool			all_isspace(const char *input);

// Functions from src/utils.c
int				is_redirect(char *token);
void			free_tokens(char **tokens);
char			*clean_arg(char *arg);
void			close_all_fds_except(int keep1, int keep2, int keep3);
void			cleanup_proc_fds(int orig_stdin, int orig_stdout);

#endif