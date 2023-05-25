# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 14:49:17 by jlaiti            #+#    #+#              #
#    Updated: 2023/05/25 15:29:48 by inaranjo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
		close_and_free_family.c \
		exec_cmd_family.c \
		init_family_proccessus.c \
		init_fd.c \
		

NAME = pipex
LIB  = libft.a

OBJS_SRCS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(LIB):
	cd libft/ && make && cp -v libft.a ../ 

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(LIB) $(OBJS_SRCS)
	$(CC) -L. -lft -o $(NAME) $(OBJS_SRCS)

clean:
	rm -rf $(OBJS_SRCS)
	${MAKE} clean -C libft

fclean: clean
	rm -rf $(NAME) $(LIB)
	${MAKE} fclean -C libft

re: fclean all

.PHONY : all clean fclean re

DEFAULT = \033[0m
GREEN = \033[1;32m
