/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:14:54 by anakin            #+#    #+#             */
/*   Updated: 2024/09/05 12:36:11 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_format(const char *str, char id)
{
	size_t	byte;

	byte = 0;
	while (str[byte] && str[byte] != id)
	byte ++;
	write(1, str, byte);
	return (byte);
}

// #include <stdio.h>

// int main (void)
// {
//     printf("%d\n",printstr("abcde",'d'));
//     printstr("abcdef%abc\n",'%');
// }