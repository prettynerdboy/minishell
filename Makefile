# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/20 05:18:48 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= libft
EPRINTF_DIR	= ft_eprintf
LIB_NAME	= $(LIB_DIR)/libft.a
EPRINTF_NAME	= $(EPRINTF_DIR)/libfteprintf.a

INCLUDES = -I include

SRC_DIR     =
BUILTIN_DIR = $(SRC_DIR)builtin
EXPAND_DIR  = $(SRC_DIR)expand
REDIRECT_DIR = $(SRC_DIR)redirect

BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, builtin.c ft_export.c ft_unset.c ft_cd.c ft_env.c ft_echo.c ft_exit.c ft_pwd.c)
EXPAND_SRCS  = $(addprefix $(EXPAND_DIR)/, expand_tokens.c expand_word.c expand_quote.c expand_var.c)
REDIRECT_SRCS  = $(addprefix $(REDIRECT_DIR)/, redirect_heredoc.c redirect.c)

SRCS = $(addprefix $(SRC_DIR), main.c parser.c signal.c tokenize.c execution.c \
                free.c error.c status.c map.c env.c) \
       $(BUILTIN_SRCS) \
       $(EXPAND_SRCS) \
	   $(REDIRECT_SRCS)
				
CC      	= cc
CFLAGS		= $(INCLUDES)
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
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(DEBUG_FLAGS)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(EPRINTF_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean
	$(MAKE) -C $(EPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re .c.o