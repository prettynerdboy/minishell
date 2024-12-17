/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:31:30 by anakin            #+#    #+#             */
/*   Updated: 2024/12/18 07:27:00 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>

size_t	print_format(const char *str, char id);
size_t	print_char(char c);
size_t	print_str(const char *str);
size_t	print_num(long long i, char id);
size_t	print_hexnum(unsigned long h, char id);
size_t	print_ptr(void *ptr);
int		ft_printf(const char *str, ...);

#endif