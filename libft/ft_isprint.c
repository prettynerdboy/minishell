/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:30:07 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:11:44 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d\n", ft_isprint('a'));
// 	printf("%d\n", ft_isprint('a'));
// 	printf("%d\n", ft_isprint(12));
// 	printf("%d\n", ft_isprint(12));
// 	printf("%d\n", ft_isprint('\n'));
// 	printf("%d\n", ft_isprint('\n'));
// }
