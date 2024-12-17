/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:53:46 by anakin            #+#    #+#             */
/*   Updated: 2024/09/05 11:22:01 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_ptr(void *ptr)
{
	size_t	len;

	if (!ptr)
		return (print_str("(nil)"));
	len = write(1, "0x", 2);
	return (print_hexnum((unsigned long)ptr, 'x') + len);
}

//！ptrは環境によるかもなので注意

// #include <stdio.h>

// int main (void)
// {
//     int i=1;
//     int *ptr;
//     printf("%p\n",ptr);
//     printf("%p\n",&i);
//     print_ptr(ptr);
//     print_ptr(&i);
// }