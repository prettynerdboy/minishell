/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:24:45 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:12:10 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	size_t			i;
	unsigned char	*string;

	i = 0;
	string = s;
	while (i < size)
	{
		string[i] = c;
		i++;
	}
	return (string);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	int	s1[] = "abcdefg";
// 	int	s2[] = "abcdefg";

// 	printf("%s\n", memset(s1, 'x', 5));
// 	printf("%s\n", ft_memset(s1, 'x', 5));
// }
