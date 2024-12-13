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
	int len = 0;

	while (tok != NULL && tok->type != TK_EOF)
	{
		len++;
		tok = tok->next;
	}
	return (len);
}


int is_blank(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_meta(char c)
{
	if (is_blank(c) || (c && ft_strchr("|<>&()\n", c)))
		return (1);
	else
		return (0);
}

int	is_word(char c)
{
	if (c && !is_meta(c))
		return (1);
	else
		return (0);
}

// TODO &の処理を考える
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
	perror("Unexpected operator");
	return (NULL);
}

bool handle_quote(char **line, char quote_type, t_quote_state *quote)
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
			return true;
		}
		(*line)++;
	}
	return false;
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;
	t_quote_state quote = {false, false};

	while (*line && !is_meta(*line))
	{
		if (*line == SINGLE_QUOTE && !quote.in_double_quote)
		{
			if (!handle_quote(&line, SINGLE_QUOTE, &quote))
			{
				perror("Unclosed quote");
				return NULL;
			}
			continue;
		}
		else if (*line == DOUBLE_QUOTE && !quote.in_single_quote)
		{
			if (!handle_quote(&line, DOUBLE_QUOTE, &quote))
			{
				perror("Unclosed quote");
				return NULL;
			}
			continue;
		}
		line++;
	}
	if (quote.in_single_quote || quote.in_double_quote)//冗長かも
	{
		perror("Unclosed quote");
		return NULL;
	}
	word = ft_strndup(start, line - start);
	if (!word)
		return NULL;
	*rest = line;
	return new_token(word, TK_WORD);
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
		else if (is_meta(*line))
		{
			tok->next = operator(&line, line);
			if (tok->next == NULL)
			{
				free_token_list(&head.next);
				return (NULL);
			}
			tok = tok->next;
		}
		else if (is_word(*line))
		{
			tok->next = word(&line, line);
			if (tok->next == NULL)
			{
				free_token_list(&head.next);
				return (NULL);
			}
			tok = tok->next;
		}
		else
		{
			free_token_list(&head.next);
			ft_putstr_fd("minishell: syntax error near unexpected token\n", STDERR_FILENO);
			return (NULL);
		}
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}


//↓構文のエラーチェック
static bool check_pipe_error(t_token *current)
{
    if (!current->next || current->next->type == TK_EOF)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
        return false;
    }
    if (token_is(current->next, "|"))
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
        return false;
    }
    return true;
}

static bool is_redirect_token(t_token *token)
{
    return (token_is(token, ">") || token_is(token, "<") || 
            token_is(token, ">>") || token_is(token, "<<"));
}

static bool check_redirect_filename_error(t_token *current)
{
    if (!current->next || current->next->type != TK_WORD)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
        return false;
    }
    return true;
}

static bool check_consecutive_redirect_error(t_token *current)
{
    if (is_redirect_token(current) && is_redirect_token(current->next))
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
        ft_putstr_fd(current->next->word, STDERR_FILENO);
        ft_putstr_fd("'\n", STDERR_FILENO);
        return false;
    }
    return true;
}

bool check_syntax_error(t_token *tokens)
{
    t_token *current = tokens;

    while (current && current->type != TK_EOF)
    {
        if (token_is(current, "|") && !check_pipe_error(current))
            return false;
        if (is_redirect_token(current) && !check_redirect_filename_error(current))
            return false;
        if (!check_consecutive_redirect_error(current))
            return false;
        current = current->next;
    }
    return true;
}
