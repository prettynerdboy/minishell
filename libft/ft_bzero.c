/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:08:42 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/21 18:12:42 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char	s1[10] = "abcdefg";
// 	char	s2[10] = "abcdefg";

// 	printf("%s\n", bzero(s1, 1));
// 	ft_bzero(s2, 1);
// 	printf("%s\n", s2);
// }
