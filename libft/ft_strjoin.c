/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 08:37:38 by anakin            #+#    #+#             */
/*   Updated: 2024/08/21 21:19:14 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sumlen;
	size_t	i;
	char	*dest;
	char	*s_1;
	char	*s_2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	sumlen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	dest = (char *)ft_calloc(sumlen + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	s_1 = (char *)s1;
	s_2 = (char *)s2;
	while (*s_1)
		dest[i++] = *s_1++;
	while (*s_2)
		dest[i++] = *s_2++;
	dest[i] = '\0';
	return (dest);
}
