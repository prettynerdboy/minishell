/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:31:49 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:12:34 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen((char *)src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	a[10] = "hello";
// 	char	b[10] = "world!";
// 	char	c[10] = "hello";
// 	char	d[10] = "world!";
// 	int		len1;
// 	int		len2;

// 	len1 = strlcpy(a, b, 3);
// 	len2 = ft_strlcpy(c, d, 3);
// 	printf("%d\n", len1);
// 	printf("%s\n", a);
// 	printf("%d\n", len2);
// 	printf("%s\n", c);
// }
