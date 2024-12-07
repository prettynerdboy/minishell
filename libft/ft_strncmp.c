/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 02:01:16 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/17 15:06:40 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if ((s1 == NULL && s2 == NULL) || n == 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include<stdio.h>
// #include<string.h>
// int	main(void)
// {
// 	printf("%d\n", strncmp("Hello", "HelloWorld", 12));
// 	printf("%d\n", strncmp("iloveshinjyuku", "ilove42", 6));
// 	printf("%d\n", strncmp("ilove42", "iloveshinjyuku", 6));
// 	printf("\n");
// 	printf("%d\n", ft_strncmp("Hello", "HelloWorld", 12));
// 	printf("%d\n", ft_strncmp("iloveshinjyuku", "ilove42", 6));
// 	printf("%d\n", ft_strncmp("ilove42", "iloveshinjyuku", 6));
// 	return (0);
// }
