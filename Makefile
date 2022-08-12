# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 20:05:07 by lholdo            #+#    #+#              #
#    Updated: 2022/01/24 20:05:08 by lholdo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME = minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LINK_READLINE = -Llib/readline/lib -lreadline -lhistory
LINK_LIBFT = -Llib/libft -lft

LIBFT = ./lib/libft/

INC = $(shell find inc -name '*.h')
INC_DIR = -Iinc

INC_READLINE = -Ilib/readline/include
INC_LIBFT = -Ilib/libft

SRC = $(shell find src -name '*.c')
OBJ = $(SRC:%.c=%.o)

RM = rm -rf

all: lib $(NAME)

lib:
	@make -C $(LIBFT)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC_DIR) $(LINK_READLINE) $(LINK_LIBFT) $^ -o $@

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $(INC_DIR) $(INC_READLINE) $(INC_LIBFT) $< -c -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all lib clean fclean re