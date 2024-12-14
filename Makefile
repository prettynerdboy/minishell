# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/14 22:03:51 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= libft
LIB_NAME	= $(LIB_DIR)/libft.a
SRCS    	= main.c parser.c signal.c tokenize.c execution.c error.c free.c redirect.c
OBJS    	= $(SRCS:.c=.o)
CC      	= cc
LDFLAGS		= -I $(LIB_DIR) $(LIB_NAME) -lreadline

# TODO CFLAGS 後で追加
# CFLAGS  = -Wall -Wextra -Werror
DEBUG_FLAGS = -g

all: $(LIB_NAME) $(NAME)

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

# TODO CFLAGS 後で追加する
$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(DEBUG_FLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o