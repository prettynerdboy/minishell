/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:59:09 by anakin            #+#    #+#             */
/*   Updated: 2024/12/07 13:59:48 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*buff;
	size_t	len;
	if (s == NULL)
		return (NULL);

	len = ft_strlen(s);
	if (len > n)
		len = n;

	buff = (char *)malloc(len + 1); 
	if (buff == NULL)
		return (NULL);
	ft_strlcpy(buff, s, len + 1); 
	return (buff);
}