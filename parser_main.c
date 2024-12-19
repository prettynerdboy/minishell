#include "minishell.h"

t_node	*make_cmd_node(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (tok && !check_eof(tok) && !token_is(tok, "|") && !token_is(tok, "\n"))
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
		else if (token_is(tok, ">>") && tok->next->type == TK_WORD)
			add_node(&node->redirects, redirect_append(&tok, tok));
		else if (token_is(tok, "<<") && tok->next->type == TK_WORD)
			add_node(&node->redirects, redirect_heredoc(&tok, tok));
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


