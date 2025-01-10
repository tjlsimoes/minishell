# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:38:14 by asafrono          #+#    #+#              #
#    Updated: 2024/12/20 14:10:43 by asafrono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC_DIR = src
OBJ_DIR = obj
BONUS_SRC_DIR = $(SRC_DIR)/bonus
PRINTF_SRC_DIR = $(SRC_DIR)/ft_printf
GNL_SRC_DIR = $(SRC_DIR)/get_next_line

LIBFT_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_utoa_base.c ft_utoa.c ft_putnbr_base.c ft_is_valid_number.c \
		ft_isspace.c ft_qsort.c ft_atodbl.c

PRINTF_SRCS = ft_printf.c handle_char.c handle_format.c \
		handle_hex_lower.c handle_hex_upper.c handle_int.c \
		handle_percent.c handle_pointer.c handle_string.c \
		handle_unsigned.c

BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
             ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
             ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

GNL_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

SRCS = $(addprefix $(SRC_DIR)/, $(LIBFT_SRCS)) \
       $(addprefix $(PRINTF_SRC_DIR)/, $(PRINTF_SRCS)) \
       $(addprefix $(GNL_SRC_DIR)/, $(GNL_SRCS))
BONUS_SRCS_FULL = $(addprefix $(BONUS_SRC_DIR)/, $(BONUS_SRCS))

OBJS = $(addprefix $(OBJ_DIR)/, $(LIBFT_SRCS:.c=.o) $(PRINTF_SRCS:.c=.o) $(GNL_SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	touch .bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PRINTF_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -s clean_silent

clean_silent:
	$(RM) -r $(OBJ_DIR)
	$(RM) .bonus

fclean: clean
	@$(MAKE) -s fclean_silent

fclean_silent:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus