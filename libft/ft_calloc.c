/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:43:39 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/28 11:26:54 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb && size && nmemb > SIZE_MAX / size)
		return (0);
	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}

// #include<stdio.h>
// int main(void)
// {
// 	int i=0;
// 	char *a=ft_calloc(4,4);
// 	while(a[i]!='\0')
// 	{
// 		printf("%c",a[i]);
// 		i++;
// 	}
// }
