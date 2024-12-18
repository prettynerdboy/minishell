/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:32:40 by anakin            #+#    #+#             */
/*   Updated: 2024/12/18 22:50:52 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"
#include<stdio.h>

static size_t	get_udigits(unsigned int n)
{
	if (n < 10)
		return (1);
	return (1 + get_udigits(n / 10));
}

static char	*unsigned_itoa(unsigned int n)
{
	char			*str_num;
	size_t			digits;
	unsigned long	num;

	num = n;
	digits = get_udigits(n);
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	return (str_num);
}

size_t	print_num(long long i, const char id)
{
	char	*str;
	size_t	len;

	str = NULL;
	if (id == 'd' || id == 'i')
		str = ft_itoa((int)i);
	else if (id == 'u')
		str = unsigned_itoa((unsigned)i);
	ft_putstr_fd(str, 2);
	len = ft_strlen(str);
	free(str);
	return (len);
}
//仮引数をintにしても同じエラーがでる。

// #include <stdio.h>

//test unsigned itoa
// int main(void)
// {
// 	unsigned int i;
// 	unsigned long b;
// 	unsigned int c;
// 	i=4294967295;
// 	b=4294967296;
// 	c=0;
// 	printf("%s\n",unsigned_itoa(i));
// 	printf("%s\n",unsigned_itoa(b));
// 	printf("%s\n",unsigned_itoa(c));
// }

// test printnum
// int main(void)
// {
//     printf("%zu\n",print_num(-2147483648,'d'));
//     printf("%zu\n",print_num(0,'d'));
//     printf("%zu\n",print_num(2147483647,'d'));
//     printf("%zu\n",print_num(-2147483648,'i'));
//     printf("%zu\n",print_num(0,'i'));
//     printf("%zu\n",print_num(2147483647,'i'));
//     printf("%zu\n",print_num(4294967295,'u'));
//     printf("%zu\n",print_num(0,'u'));
// }