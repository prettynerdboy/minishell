/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:16:33 by anakin            #+#    #+#             */
/*   Updated: 2024/08/28 11:31:27 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	index;
	unsigned int	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen((char *)s);
	p = (char *)malloc(len + 1);
	if (p == NULL)
		return (NULL);
	index = 0;
	if (f == NULL)
		ft_strlcpy(p, s, len);
	else
	{
		while (index < len)
		{
			p[index] = (*f)(index, s[index]);
			index++;
		}
		p[len] = '\0';
	}
	return (p);
}
