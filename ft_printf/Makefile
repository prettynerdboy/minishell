# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 11:37:18 by anakin            #+#    #+#              #
#    Updated: 2024/12/18 07:28:18 by soaoki           ###   ########.fr        #
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
	$(MAKE) -C ./libft
	cp ../libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJ)

clean:
	$(MAKE) clean -C ../libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C ../libft
	rm -f $(NAME)

re: fclean all