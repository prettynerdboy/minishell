/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:02:47 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:11:52 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;

	d = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		if (*d == (unsigned char)c)
		{
			return (d);
		}
		i++;
		d++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	test1[10] = "abcde";
// 	char	test2[10] = "abcde";

// 	printf("memchr\n");
// 	printf("%s\n", memchr(test1, 'c', 2));
// 	printf("%s\n", memchr(test1, 'a', 2));
// 	printf("%s\n", memchr(test1, 'c', 3));
// 	printf("%s\n", memchr(test1, 'z', 5));
// 	printf("ft_memchr\n");
// 	printf("%s\n", ft_memchr(test1, 'c', 2));
// 	printf("%s\n", ft_memchr(test1, 'a', 2));
// 	printf("%s\n", ft_memchr(test1, 'c', 3));
// 	printf("%s\n", ft_memchr(test1, 'z', 5));
// }
