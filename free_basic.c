#include "minishell.h"

void	free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_node(t_node **node)
{
	if (!node || !*node)
		return ;
	free_token_list(&(*node)->args);
	if ((*node)->filename)
	{
		free((*node)->filename->word);
		free((*node)->filename);
		(*node)->filename = NULL;
	}
	if ((*node)->delimiter)
	{
		free((*node)->delimiter->word);
		free((*node)->delimiter);
		(*node)->delimiter = NULL;
	}
	free_node(&(*node)->redirects);
	free_node(&(*node)->command);
	free_node(&(*node)->next);
	free(*node);
	*node = NULL;
}

void	wp_free(char ***str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
}

void	free_envmap(void)
{
	t_item	*cur;
	t_item	*tmp;
	t_map	**envmap;

	envmap = get_envmap();
	cur = (*envmap)->item_head.next;
	fflush(0);
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	free(*envmap);
	*envmap = NULL;
}

