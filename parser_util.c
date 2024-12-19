#include "minishell.h"

int	check_eof(t_token *tok)
{
	if (tok->type == TK_EOF)
		return (1);
	else
		return (0);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(*node));
	node->kind = kind;
	return (node);
}

void	add_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	add_node(&(*node)->next, elm);
}
