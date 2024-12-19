/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 05:21:41 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:17:01 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	envmap_init(t_map *map, char **ep)
{
	while (*ep)
	{
		map_initialize(map, *ep);
		ep++;
	}
}

char	*xgetenv(const char *name)
{
	return (map_get(*get_envmap(), name));
}

void	initenv(void)
{
	extern char	**environ;
	t_map		**envmap;

	envmap = get_envmap();
	*envmap = map_new();
	envmap_init(*envmap, environ);
}

char	**get_environ(t_map *map)
{
	size_t	i;
	size_t	size;
	t_item	*item;
	char	**environ;

	size = map_len(map, false) + 1;
	environ = malloc(sizeof(char *) * size);
	i = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value)
		{
			environ[i] = item_get_string(item);
			i++;
		}
		item = item->next;
	}
	environ[i] = NULL;
	return (environ);
}
