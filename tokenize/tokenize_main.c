#include "minishell.h"

t_token	*operator(char **rest, char *line)
{
	size_t	total_op;
	size_t	op_len;
	size_t	i;
	char	*op;

	static char *const operators[] = {">>", "<<", "<", ">", "|", "\n"};
	total_op = sizeof(operators) / sizeof(*operators);
	i = 0;
	while (i < total_op)
	{
		op_len = ft_strlen(operators[i]);
		if (ft_strncmp(line, operators[i], op_len) == 0)
		{
			op = ft_strdup(operators[i]);
			*rest = line + op_len;
			return (new_token(op, TK_OP));
		}
		i++;
	}
	ft_eprintf("Unexpected operator\n");
	return (NULL);
}

bool	handle_quote(char **line, char quote_type, t_quote_state *quote)
{
	(*line)++;
	if (quote_type == SINGLE_QUOTE)
		quote->in_single_quote = true;
	else if (quote_type == DOUBLE_QUOTE)
		quote->in_double_quote = true;
	while (**line)
	{
		if (**line == quote_type)
		{
			(*line)++;
			if (quote_type == SINGLE_QUOTE)
				quote->in_single_quote = false;
			else if (quote_type == DOUBLE_QUOTE)
				quote->in_double_quote = false;
			return (true);
		}
		(*line)++;
	}
	return (false);
}

t_token	*word(char **rest, char *line)
{
	const char		*start = line;
	char			*word;
	t_quote_state	quote;

	quote = (t_quote_state){false, false};
	while (*line)
	{
		if (*line == SINGLE_QUOTE && !quote.in_double_quote)
		{
			if (!handle_quote(&line, SINGLE_QUOTE, &quote))
			{
				ft_eprintf("Unclosed quote\n");
				return (NULL);
			}
			continue ;
		}
		else if (*line == DOUBLE_QUOTE && !quote.in_single_quote)
		{
			if (!handle_quote(&line, DOUBLE_QUOTE, &quote))
			{
				ft_eprintf("Unclosed quote\n");
				return (NULL);
			}
			continue ;
		}
		if (!quote.in_single_quote && !quote.in_double_quote && is_meta(*line))
			break;
		line++;
	}
	if (quote.in_single_quote || quote.in_double_quote) //冗長かも
	{
		ft_eprintf("Unclosed quote\n");
		return (NULL);
	}
	word = ft_strndup(start, line - start);
	if (!word)
		return (NULL);
	*rest = line;
	return (new_token(word, TK_WORD));
}

t_token	*tokenizer(char *line)
{
	t_token	head;
	t_token	*tok;

	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (is_blank(*line))
			line++;
		else if (is_meta(*line) && !is_word(*line))
		{
			tok->next = operator(&line, line);
			if (tok->next == NULL)
			{
				free_token_list(&head.next);
				return (NULL);
			}
			tok = tok->next;
		}
		else
		{
			tok->next = word(&line, line);
			if (tok->next == NULL)
			{
				free_token_list(&head.next);
				return (NULL);
			}
			tok = tok->next;
		}
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}

