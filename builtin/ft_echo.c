/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:16:43 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 03:11:20 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	n_option;
	int	j;

	n_option = 0;
	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0' || j == 1)
			break ;
		n_option = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
