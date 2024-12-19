#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}
bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}
t_item	*item_new(char *name, char *value)
{
	t_item	*item;

	item = (t_item *)malloc(sizeof(t_item));
	if (item == NULL)
		perror("malloc");
	item->name = name;
	item->value = value;
	return (item);
}
char	*item_get_string(t_item *item)
{
	size_t	strsize;
	char	*string;

	strsize = ft_strlen(item->name) + 2;
	if (item->value)
		strsize += ft_strlen(item->value);
	string = (char *)malloc(sizeof(char) * strsize);
	if (string == NULL)
		perror("malloc");
	ft_strlcpy(string, item->name, strsize);
	if (item->value)
	{
		ft_strlcat(string, "=", strsize);
		ft_strlcat(string, item->value, strsize);
	}
	return (string);
}
t_map	*map_new(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->item_head.next = NULL;
	map->item_head.value = NULL;
	map->item_head.name = NULL;
	if (map == NULL)
		perror("malloc");
	return (map);
}
char	*map_get(t_map *map, const char *name)
{
	t_item	*cur;

	if (name == NULL)
		return (NULL);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}
int	map_unset(t_map *map, const char *name)
{
	t_item	*cur;
	t_item	*prev;

	if (name == NULL || !is_identifier(name))
		return (-1);
	prev = &map->item_head;
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			prev->next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = prev->next;
		cur = cur->next;
	}
	return (0);
}

int	value_initialize(const char *string, char **name, char **value,
		bool allow_empty_value)
{
	char	*name_end;

	name_end = ft_strchr(string, '=');
	if (!name_end && !allow_empty_value)
		return (0);
	if (!name_end)
	{
		*name = ft_strdup(string);
		*value = NULL;
		if (!name)
			perror("strdup");
	}
	// value is non null
	else
	{
		*name = ft_strndup(string, name_end - string);
		*value = ft_strdup(name_end + 1);
		if (*name == NULL || *value == NULL)
			perror("strdup");
	}
	return (1);
}

void	put_cur(t_item **cur, const char *name, const char *value)
{
	if (name == NULL && value == NULL)
		perror("strdup");
	if (value == NULL)
	{
		*cur = item_new(ft_strdup(name), NULL);
		if ((*cur)->name == NULL)
			perror("strdup");
	}
	else
	{
		*cur = item_new(ft_strdup(name), ft_strdup(value));
		if ((*cur)->name == NULL || (*cur)->value == NULL)
			perror("strdup");
	}
}

void	map_initialize(t_map *map, char *string)
{
	t_item	*cur;
	char	*name;
	char	*value;

	value_initialize(string, &name, &value, false);
	put_cur(&cur, name, value);
	free(name);
	free(value);
	cur->next = map->item_head.next;
	map->item_head.next = cur;
}

int	map_set(t_map *map, const char *name, const char *value)
{
	t_item	*cur;

	if (name == NULL || !is_identifier(name))
		return (-1);
	cur = map->item_head.next;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
			break ;
		cur = cur->next;
	}
	if (cur)
	{
		free(cur->value);
		if (value == NULL)
			cur->value = NULL;
		else
		{
			cur->value = ft_strdup(value);
			if (cur->value == NULL)
				perror("map_set strdup");
		}
	}
	else
	{
		put_cur(&cur, name, value);
		cur->next = map->item_head.next;
		map->item_head.next = cur;
	}
	return (0);
}
int	map_put(t_map *map, const char *string, bool allow_empty_value)
{
	int		result;
	char	*name;
	char	*value;

	if (!value_initialize(string, &name, &value, allow_empty_value))
		return (-1);
	result = map_set(map, name, value);
	free(name);
	free(value);
	return (result);
}
size_t	map_len(t_map *map, bool count_null_value)
{
	size_t	len;
	t_item	*item;

	len = 0;
	item = map->item_head.next;
	while (item)
	{
		if (item->value || count_null_value)
			len++;
		item = item->next;
	}
	return (len);
}
