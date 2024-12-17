/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:18:00 by anakin            #+#    #+#             */
/*   Updated: 2024/09/05 12:52:12 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	change_alpha(unsigned int h)
{
	if (h == 10)
		return ('a');
	else if (h == 11)
		return ('b');
	else if (h == 12)
		return ('c');
	else if (h == 13)
		return ('d');
	else if (h == 14)
		return ('e');
	else if (h == 15)
		return ('f');
	else
		return (0);
}

static	size_t	get_hexlen(unsigned long h)
{
	size_t	hex_len;

	hex_len = 0;
	while (h)
	{
		h = h / 16;
		hex_len++;
	}
	return (hex_len);
}

char	*change_hexnum(char *string, unsigned long base, size_t len)
{
	unsigned int	mod;
	int				i;

	i = 0;
	string[len] = '\0';
	while (base)
	{
		mod = base % 16;
		if (mod >= 10)
			string[len - (1 + i)] = change_alpha(mod);
		else if (mod < 10)
			string[len - (1 + i)] = mod + '0';
		base = base / 16;
		i ++;
	}
	return (string);
}

static	char	*str_toupper(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

size_t	print_hexnum(unsigned long h, char id)
{
	size_t		hex_len;
	char		*str;

	if (h == 0)
	{
		print_char('0');
		return (1);
	}
	hex_len = get_hexlen(h);
	str = malloc((hex_len + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	str = change_hexnum(str, h, hex_len);
	if (id == 'X')
		str_toupper(str);
	print_str(str);
	free(str);
	return (hex_len);
}

// test print_hexnum
// #include <stdio.h>

// int main(void)
// {
//     // print_hexnum(0,'x');
//     // print_hexnum(9,'x');
//     // print_hexnum(15,'x');
// 	// printf("%zu\n",print_hexnum(0,'x'));
// 	// printf("%zu\n",print_hexnum(9,'x'));
// 	// printf("%zu\n",print_hexnum(15,'x'));
// 	// printf("%zu\n",print_hexnum(16,'x'));
// 	// printf("%zu\n",print_hexnum(88888,'x'));
// 	// printf("%zu\n",print_hexnum(4294967295,'x'));
//     // printf("%zu\n",print_hexnum(0,'X'));
// 	// printf("%zu\n",print_hexnum(9,'X'));
// 	// printf("%zu\n",print_hexnum(15,'X'));
// 	// printf("%zu\n",print_hexnum(16,'X'));
// 	// printf("%zu\n",print_hexnum(88888,'X'));
// 	// printf("%zu\n",print_hexnum(4294967295,'X'));
// 	// return(0);
// }