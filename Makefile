# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 17:18:15 by asafrono          #+#    #+#              #
#    Updated: 2025/03/29 17:10:53 by tjorge-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -D MAX_INPUT_LENGTH=$(MAX_INPUT_LENGTH) -I$(LIBFT_DIR) -I$(SRC_DIR)
DEBUG_FLAGS = -g
RM = rm -rf

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c ast.c tokenizer.c tokenizer_utils.c utils.c signals_a.c signals_b.c error_handling.c \
parser.c parser_redirect_a.c parser_redirect_b.c parser_pipe.c parser_env.c \
parser_env_split.c parser_env_utils.c parser_argument.c \
env_tests.c env_vars_change.c env_vars_expand.c env_vars_get_a.c env_vars_get_b.c \
env_vars_print.c env_vars_utils_a.c env_vars_utils_b.c env_vars_utils_c.c\
builtins_cd_a.c builtins_cd_b.c builtins_env.c builtins_env_utils.c builtins_pwd_echo.c builtins_tests.c \
executor_builtins_a.c executor_gen.c executor_main_a.c executor_main_b.c executor_main_c.c executor_path_res_abs_path.c \
executor_path_res_a.c executor_path_res_b.c executor_path_res_split.c executor_path_res_utils_a.c executor_path_res_utils_b.c \
executor_redirect_gen_a.c executor_redirect_gen_b.c executor_redirect_gen_c.c executor_redirect_gen_d.c executor_redirect_gen_e.c \
executor_redirect_gen_utils.c executor_redirect_get.c executor_redirect_get_utils.c executor_tests.c executor_utils.c \
exit_status.c builtins_exit.c executor_path_res_check_abs.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
MAX_INPUT_LENGTH = 1024
# Valgrind flags
VFLAGS = -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=valgrind_readline.supp

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

child: VFLAGS = -s --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=valgrind_readline.supp
child: $(NAME)
	valgrind $(VFLAGS) ./$(NAME)

run: $(NAME)
	valgrind $(VFLAGS) ./$(NAME)

debug: CFLAGS = -g -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(SRC_DIR)
debug: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

rdebug: debug
	valgrind $(VFLAGS) ./$(NAME)
.PHONY: all clean fclean re
