/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:21:59 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:12:30 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	else if (dest_len < size)
	{
		while (src[i] != '\0' && dest_len < size - 1)
		{
			dest[dest_len] = src[i];
			i++;
			dest_len++;
		}
		dest[dest_len] = '\0';
		return (dest_len + src_len - i);
	}
	else
		return (src_len + size);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	a[100] = "abcde";
// 	char	b[100] = "123";
// 	int		i;
// 	char	c[100] = "abcde";
// 	char	d[100] = "123";

// 	printf("%s :%s\n", a, b);
// 	i = strlcat(a, b, 9);
// 	printf("%s / %d\n", a, i);
// 	printf("%s :%s\n", c, d);
// 	i = ft_strlcat(c, d, 9);
// 	printf("%s / %d\n", c, i);
// }
