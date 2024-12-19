/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 05:29:58 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:08:51 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_allenv(void)
{
	t_item	*cur;
	t_map	*envmap;

	envmap = *get_envmap();
	cur = envmap->item_head.next;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->name, cur->value);
		else
			printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}
int	ft_export(char **argv)
{
	size_t i;
	int status;
	t_map *envmap;

	envmap = *get_envmap();
	if (argv[1] == NULL)
	{
		print_allenv();
		return (0);
	}
	status = 0;
	i = 1;
	while (argv[i])
	{
		if (map_put(envmap, argv[i], true) < 0)
		{
			ft_eprintf("export: %s not a valid identifier\n", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}