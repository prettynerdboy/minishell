/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:34:47 by soaoki            #+#    #+#             */
/*   Updated: 2024/08/22 16:11:38 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", ft_isdigit('0'));
// 	printf("%d\n", isdigit('0'));
// 	printf("%d\n", ft_isdigit('a'));
// 	printf("%d\n", isdigit('a'));
// 	printf("%d\n", ft_isdigit('-'));
// 	printf("%d\n", isdigit('-'));
// 	return (0);
// }
