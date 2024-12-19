# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/20 05:22:56 by soaoki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= libft
EPRINTF_DIR	= ft_eprintf
LIB_NAME	= $(LIB_DIR)/libft.a
EPRINTF_NAME	= $(EPRINTF_DIR)/libfteprintf.a
SRCS    	= main.c signal.c expand.c \
				redirect.c map.c env.c \
				builtin/builtin.c builtin/ft_export.c builtin/ft_unset.c builtin/ft_env.c \
				builtin/ft_echo.c builtin/ft_exit.c builtin/ft_pwd.c builtin/ft_cd.c\
				tokenize_is.c tokenize_util.c tokenize_main.c tokenize_syntax.c\
				execution_buitin.c execution_path.c execution_pipe.c\
				execution_util.c execution_wait.c execution_main.c\
				free_basic.c free_wrap.c\
				parser_main.c parser_util.c parser_redirect.c\
				status_is.c status_get.c\
				
				
				
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