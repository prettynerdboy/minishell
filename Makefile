# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/19 09:31:48 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= libft
EPRINTF_DIR	= ft_eprintf
LIB_NAME	= $(LIB_DIR)/libft.a
EPRINTF_NAME	= $(EPRINTF_DIR)/libfteprintf.a
SRCS    	= main.c parser.c signal.c tokenize.c execution.c expand.c \
				free.c redirect.c error.c status.c map.c env.c \
				builtin/builtin.c builtin/ft_export.c builtin/ft_unset.c builtin/ft_env.c \
				builtin/ft_echo.c builtin/ft_exit.c builtin/ft_pwd.c builtin/ft_cd.c
OBJS    	= $(SRCS:.c=.o)
CC      	= cc
LDFLAGS		= -I $(LIB_DIR) $(LIB_NAME) -I $(EPRINTF_DIR) $(EPRINTF_NAME) -lreadline

# TODO CFLAGS 後で追加
# CFLAGS  = -Wall -Wextra -Werror
DEBUG_FLAGS = -g

all: $(LIB_NAME) $(EPRINTF_NAME) $(NAME)

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(EPRINTF_NAME):
	$(MAKE) -C $(EPRINTF_DIR)

# TODO CFLAGS 後で追加する
$(NAME): $(SRCS)
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