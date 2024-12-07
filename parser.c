#include "minishell.h"

int	check_eof(t_token *tok)
{
	if (tok->type == TK_EOF)
		return (1);
	else
		return (0);
}

int	token_is(t_token *token, const char *str)
{
	size_t	i;

	i = 0;
	if (!token || !token->word || !str)
		return (-1);
	while (token->word[i] && str[i])
	{
		if (token->word[i] != str[i])
			return (0);
		i++;
	}
	if (token->word[i] == '\0' && str[i] == '\0')
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

t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokencpy(tok->next);
	node->targetfd = -1;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_in(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN);
	node->filename = tokencpy(tok->next);
	node->targetfd = -1;
	*rest = tok->next->next;
	return (node);
}

t_node	*make_cmd_node(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (tok && !check_eof(tok) && !token_is(tok, "|") && !token_is(tok,
			"\n"))
	{
		if (tok->type == TK_WORD)
		{
			add_token(&node->args, tokencpy(tok));
			tok = tok->next;
		}
		else if (token_is(tok, ">") && tok->next && tok->next->type == TK_WORD)
			add_node(&node->redirects, redirect_out(&tok, tok));
		else if (token_is(tok, "<") && tok->next && tok->next->type == TK_WORD)
			add_node(&node->redirects, redirect_in(&tok, tok));
		// add other redirect
		else
			perror("parse,error");
	}
	*rest = tok;
	return (node);
}

t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_node	*node;

	if (!tok || tok->type == TK_EOF)
	{
		*rest = tok;
		return (NULL);
	}
	node = new_node(ND_PIPELINE);
	ft_memset(node->inpipe, -1, sizeof(node->inpipe));
	ft_memset(node->outpipe, -1, sizeof(node->outpipe));
	node->command = make_cmd_node(&tok, tok);
	if (tok && token_is(tok, "|"))
		node->next = pipeline(&tok, tok->next);
	*rest = tok;
	return (node);
}

t_node	*parser(t_token *tok)
{
	return (pipeline(&tok, tok));
}
