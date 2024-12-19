#include "minishell.h"

void	exit_with_status(t_data *data, int status)
{
	free_envmap();
	free_data(&data);
	exit(status);
}

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	if ((*data)->tokens)
		free_token_list(&(*data)->tokens);
	if ((*data)->nodes)
		free_node(&(*data)->nodes);
	*data = NULL;
}
