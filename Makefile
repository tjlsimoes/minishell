# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 17:18:15 by asafrono          #+#    #+#              #
#    Updated: 2025/02/06 16:26:52 by tjorge-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(SRC_DIR)
RM = rm -rf

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c ast.c tokenizer.c utils.c signals.c error_handling.c \
parser.c parser_redirect.c parser_pipe.c parser_env.c parser_argument.c \
env_tests.c env_vars_a.c env_vars_b.c env_vars_c.c env_vars_d.c env_vars_e.c env_vars_f.c\
builtins_tests.c builtins_a.c builtins_b.c builtins_c.c builtins_d.c \
executor_a.c executor_b.c executor_tests.c \
exit_status.c 

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

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

run: $(NAME)
	valgrind $(VFLAGS) ./$(NAME)

.PHONY: all clean fclean re
