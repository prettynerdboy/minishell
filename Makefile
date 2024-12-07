# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/07 18:01:16 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_NAME	= libft.a
SRCS    	= main.c parser.c signal.c tokenize.c
OBJS    	= $(SRCS:.c=.o)
CC      	= cc
# TODO CFLAGS 後で追加
# CFLAGS  = -Wall -Wextra -Werror
DEBUG_FLAGS = -g

$(LIB_NAME):
	$(MAKE) -C libft

# TODO CFLAGS 後で追加する
$(NAME): $(OBJS)
	$(CC) $^ -o $@ -I libft libft/$(LIB_NAME) -lreadline

all: $(LIB_NAME) $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re .c.o