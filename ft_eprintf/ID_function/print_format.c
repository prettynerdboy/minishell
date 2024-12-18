/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:14:54 by anakin            #+#    #+#             */
/*   Updated: 2024/12/18 22:49:23 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"

size_t	print_format(const char *str, char id)
{
	size_t	byte;

	byte = 0;
	while (str[byte] && str[byte] != id)
	byte ++;
	write(2, str, byte);
	return (byte);
}

// #include <stdio.h>

// int main (void)
// {
//     printf("%d\n",printstr("abcde",'d'));
//     printstr("abcdef%abc\n",'%');
// }