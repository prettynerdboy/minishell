#include "minishell.h"

t_token	*new_token(char *word, t_token_type type)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
	if (tok == NULL)
		perror("calloc error");
	tok->word = word;
	tok->type = type;
	return (tok);
}

t_token	*tokencpy(t_token *tok)
{
	char	*word;

	word = ft_strdup(tok->word);
	return (new_token(word, tok->type));
}

void	add_token(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	add_token(&(*tok)->next, elm);
}

int	get_token_list_length(t_token *tok)
{
	int	len;

	len = 0;
	while (tok != NULL && tok->type != TK_EOF)
	{
		len++;
		tok = tok->next;
	}
	return (len);
}

int	token_is(t_token *token, const char *str)
{
	size_t	i;

	i = 0;
	if (!token || !token->word || !str)
		return (-1);
	if (token->type != TK_OP && ft_strchr("|<>", str[0]))
		return (0);
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
