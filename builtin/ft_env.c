/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:13:00 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:08:47 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv)
{
	t_item *cur;
	(void)argv;
	cur = (*get_envmap())->item_head.next;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
	printf("_=/usr/bin/env\n");
	return (0);
}