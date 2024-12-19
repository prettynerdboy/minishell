/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:08:26 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/19 10:45:41 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **argv)
{
	int		status;
	size_t	i;

	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_unset(*get_envmap(), argv[i]) < 0)
		{
			ft_eprintf("unset: %s not a valid identifier\n", argv[i]);
			status = 1;
		}
		else
			status = 0;
		i++;
	}
	return (status);
}
