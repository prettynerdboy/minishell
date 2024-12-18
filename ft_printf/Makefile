# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 11:37:18 by anakin            #+#    #+#              #
#    Updated: 2024/12/18 10:36:19 by hauchida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS =  -Wall -Wextra -Werror -I. -c
FILES = ft_printf.c\
			ID_function/print_char.c\
			ID_function/print_format.c\
			ID_function/print_hexnum.c\
			ID_function/print_num.c\
			ID_function/print_ptr.c\
			ID_function/print_str.c\

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all