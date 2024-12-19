/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:10:04 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:12:01 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*c;
	char	*d;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	c = (char *)dst;
	d = (char *)src;
	while (i < n)
	{
		c[i] = d[i];
		i++;
	}
	return (c);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	a[10] = "aaaaaaaa";
// 	char	b[10] = "123456";

// 	ft_memcpy(a, b, 2);
// 	printf("%s\n", a);
// }
