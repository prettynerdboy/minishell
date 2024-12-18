/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:31:30 by anakin            #+#    #+#             */
/*   Updated: 2024/12/18 23:44:28 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EPRINTF_H
# define FT_EPRINTF_H
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>

size_t	print_format(const char *str, char id);
size_t	print_char(char c);
size_t	print_str(const char *str);
size_t	print_num(long long i, char id);
size_t	print_hexnum(unsigned long h, char id);
size_t	print_ptr(void *ptr);
int		ft_eprintf(const char *str, ...);

#endif