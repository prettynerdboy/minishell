/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:31:49 by anakin            #+#    #+#             */
/*   Updated: 2024/12/18 23:44:57 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"

int	check_id( const char *id, va_list ap)
{
	if (*id == 'c')
		return (print_char(va_arg(ap, int)));
	if (*id == 's')
		return (print_str(va_arg(ap, char *)));
	if (*id == 'd' || *id == 'i')
		return (print_num(va_arg(ap, int),*id));
	if (*id == 'u')
		return (print_num(va_arg(ap, unsigned int),*id));
	if (*id == 'x' || *id == 'X' )
		return (print_hexnum(va_arg(ap, unsigned int),*id));
	if (*id == 'p')
		return (print_ptr(va_arg(ap, void *)));
	if (*id == '%')
		return (print_char('%'));
	else
		print_str("%\n");
	return (2);
}

int	ft_eprintf(const char *format, ...)
{
	size_t	len;
	size_t	count;
	va_list	ap;

	va_start(ap, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len = len + check_id(format, ap);
			format++;
		}
		else
		{
			count = print_format(format, '%');
			format = format + count;
			len = len + count;
		}
	}
	va_end(ap);
	return ((int)len);
}
