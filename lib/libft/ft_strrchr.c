/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 01:17:11 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:12:47 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		s_len;
	char	*buff;
	char	*result;

	i = 0;
	buff = (char *)s;
	result = buff;
	s_len = (int)ft_strlen(buff);
	while (i < s_len)
	{
		if (*buff == (char)c)
			result = (char *)buff;
		buff++;
		i++;
	}
	if ((char)c == '\0')
		return (buff);
	if (*result == (char)c)
		return (result);
	return (0);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	test1[20] = "ilove42tokyo";
// 	char	test2[20] = "ilove42tokyo";

// 	printf("%s\n", strrchr(test1, 'i'));
// 	printf("%s\n", strrchr(test1, '\0'));
// 	printf("%s\n", strrchr(test1, 101));
// 	printf("%s\n", strrchr(test1, 'h'));
// 	printf("%s\n", ft_strrchr(test2, 'i'));
// 	printf("%s\n", ft_strrchr(test2, '\0'));
// 	printf("%s\n", ft_strrchr(test2, 101));
// 	printf("%s\n", ft_strrchr(test2, 'h'));
// }
