#include "minishell.h"

int	*get_status(void)
{
	static int	g_status;

	return (&g_status);
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

t_map	**get_envmap(void)
{
	static t_map	*envmap;

	return (&envmap);
}
