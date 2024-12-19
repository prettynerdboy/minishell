/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:19:37 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/19 13:22:06 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(char **argv)
{
	int		status;
	t_data	*data;

	data = get_data();
	if (!argv[1])
	{
		printf("exit\n");
		exit_with_status(data, 0);
	}
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit_with_status(data, 2);
	}
	status = ft_atoi(argv[1]);
	if (0 <= status && status <= 255)
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit_with_status(data, 2);
	}
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	printf("exit\n");
	exit_with_status(data, status);
	return (0);
}
