# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 04:33:27 by anakin            #+#    #+#              #
#    Updated: 2024/12/20 06:09:26 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= my_minishell
LIB_DIR		= lib/libft
EPRINTF_DIR	= lib/ft_eprintf
LIB_NAME	= $(LIB_DIR)/libft.a
EPRINTF_NAME	= $(EPRINTF_DIR)/libfteprintf.a

INCLUDES = -I include

SRC_DIR     =
BUILTIN_DIR = $(SRC_DIR)builtin
EXPAND_DIR  = $(SRC_DIR)expand
REDIRECT_DIR = $(SRC_DIR)redirect
EXECUTION_DIR = $(SRC_DIR)execution
FREE_DIR = $(SRC_DIR)free
PARSER_DIR = $(SRC_DIR)parser
TOKENIZE_DIR = $(SRC_DIR)tokenize
STATUS_DIR = $(SRC_DIR)status

BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, builtin.c ft_export.c ft_unset.c ft_cd.c ft_env.c ft_echo.c ft_exit.c ft_pwd.c)
EXPAND_SRCS  = $(addprefix $(EXPAND_DIR)/, expand_tokens.c expand_word.c expand_quote.c expand_var.c)
REDIRECT_SRCS  = $(addprefix $(REDIRECT_DIR)/, redirect_heredoc.c redirect.c)
EXECUTION_SRCS = $(addprefix $(EXECUTION_DIR)/, execution_builtin.c execution_main.c execution_path.c execution_pipe.c execution_util.c execution_wait.c)
FREE_SRCS = $(addprefix $(FREE_DIR)/, free_basic.c free_wrap.c)
PARSER_SRCS = $(addprefix $(PARSER_DIR)/, parser_main.c parser_redirect.c parser_util.c)
TOKENIZE_SRCS = $(addprefix $(TOKENIZE_DIR)/, tokenize_is.c tokenize_main.c tokenize_syntax.c tokenize_util.c)
STATUS_SRCS = $(addprefix $(STATUS_DIR)/, status_get.c status_is.c)

SRCS = $(addprefix $(SRC_DIR), main.c signal.c map.c env.c ) \
       $(BUILTIN_SRCS) \
       $(EXPAND_SRCS) \
	   $(REDIRECT_SRCS) \
	   $(EXECUTION_SRCS) \
	   $(FREE_SRCS) \
	   $(PARSER_SRCS) \
	   $(TOKENIZE_SRCS) \
	   $(STATUS_SRCS)
				
OBJS    	= $(SRCS:.c=.o)
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