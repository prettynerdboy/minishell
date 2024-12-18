# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anakin <anakin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/19 00:03:28 by anakin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= libft
EPRINTF_DIR	= ft_eprintf
LIB_NAME	= $(LIB_DIR)/libft.a
EPRINTF_NAME	= $(EPRINTF_DIR)/libfteprintf.a
SRCS    	= main.c parser.c signal.c tokenize.c execution.c expand.c free.c redirect.c error.c status.c builtin.c
OBJS    	= $(SRCS:.c=.o)
CC      	= cc
LDFLAGS		= -I $(LIB_DIR) $(LIB_NAME) -I $(EPRINTF_DIR) $(EPRINTF_NAME) -lreadline -g

# TODO CFLAGS 後で追加
# CFLAGS  = -Wall -Wextra -Werror
# DEBUG_FLAGS = -fsanitize=address

all: $(LIB_NAME) $(EPRINTF_NAME) $(NAME)

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(EPRINTF_NAME):
	$(MAKE) -C $(EPRINTF_DIR)

# TODO CFLAGS 後で追加する
$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(DEBUG_FLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(EPRINTF_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean
	$(MAKE) -C $(EPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o