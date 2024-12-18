# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/18 10:35:46 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= libft
PRINTF_DIR	= ft_printf
LIB_NAME	= $(LIB_DIR)/libft.a
PRINTF_NAME	= $(PRINTF_DIR)/libftprintf.a
SRCS    	= main.c parser.c signal.c tokenize.c execution.c expand.c free.c redirect.c error.c status.c builtin.c
OBJS    	= $(SRCS:.c=.o)
CC      	= cc
LDFLAGS		= -I $(LIB_DIR) $(LIB_NAME) -I $(PRINTF_DIR) $(PRINTF_NAME) -lreadline -g

# TODO CFLAGS 後で追加
# CFLAGS  = -Wall -Wextra -Werror
DEBUG_FLAGS = -fsanitize=address

all: $(LIB_NAME) $(PRINTF_NAME) $(NAME)

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(PRINTF_NAME):
	$(MAKE) -C $(PRINTF_DIR)

# TODO CFLAGS 後で追加する
$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(DEBUG_FLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o