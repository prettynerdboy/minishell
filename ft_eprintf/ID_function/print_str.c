/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:19:25 by anakin            #+#    #+#             */
/*   Updated: 2024/12/18 22:51:28 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"

size_t	print_str(const char *str)
{
	size_t	i;

	if (!str)
	{
		write(2, "(null)", 6);
		return (6);
	}
	i = ft_strlen(str);
	write(2, str, i);
	return (i);
}
