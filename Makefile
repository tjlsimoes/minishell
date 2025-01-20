# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 17:18:15 by asafrono          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2025/01/28 13:17:46 by asafrono         ###   ########.fr        #
=======
#    Updated: 2025/01/17 12:13:40 by tjorge-l         ###   ########.fr        #
>>>>>>> 90cd21b (Add env vars and exit status exploration)
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

<<<<<<< HEAD
SRCS = main.c ast.c parser.c parser_redirect.c tokenizer.c utils.c
=======
SRCS = main.c ast.c parser.c tokenizer.c utils.c \
env_tests.c \
exit_status.c env_vars_a.c env_vars_b.c env_vars_c.c \
env_vars_d.c signals.c
>>>>>>> 90cd21b (Add env vars and exit status exploration)

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
