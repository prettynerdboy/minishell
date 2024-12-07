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

int is_blank(char c)
{
    if(c == ' ' || c =='\n')
        return(1);
    else
        return(0);
}

int is_meta(char c)
{
	if (is_blank(c) || (c && ft_strchr("|<>\n", c)))
		return (1);
    else
        return(0);
}

int	is_word(char c)
{
	if(c && !is_meta(c))
        return(1);
    else
        return(0);
}

t_token *operator(char **rest, char *line)
{
    static char *const operators[] = {">>", "<<", "<", ">", "|", "\n"};
    size_t total_op;
    size_t op_len;
    size_t i ;
    char *op;

    total_op = sizeof(operators) / sizeof(*operators); 
    i=0;
    while (i < total_op)
    {
        op_len = ft_strlen(operators[i]);
        if (ft_strncmp(line, operators[i], op_len) == 0)
        {
            op = ft_strdup(operators[i]);
            *rest = line + op_len;
            return new_token(op, TK_OP);
        }
        i++;
    }
    perror("Unexpected operator");
    return(NULL);
}

void handle_quote(char **line, char quote_type)
{
    char *start ;
    char *result;
    start = ++(*line);
    while (**line && **line != quote_type)
        (*line)++;
    if (**line == '\0')
    {
        perror("Unclosed quote");
    }
    (*line)++; 
}

t_token *word(char **rest, char *line)
{
    const char *start = line;
    char *word;

    while (*line && !is_meta(*line))
    {
        if (*line == SINGLE_QUOTE || *line == DOUBLE_QUOTE)
        {
            handle_quote(&line, *line);
        }
        else 
            line++;
    }
    word = ft_strndup(start, line - start);
    if (!word)
        perror("strndup");
    *rest = line;
    return new_token(word, TK_WORD);
}

t_token *tokenizer(char *line)
{
    t_token head;
    t_token *tok;

    head.next = NULL; 
    tok = &head;
    while(*line)
    {
        if(is_blank(*line))
            line++;
        else if(is_meta(*line))
        {    tok->next=operator(&line,line);
            tok=tok->next;
        }
        else if(is_word(*line))
        {
            tok->next=word(&line,line);
            tok=tok->next;
        }
        else
            perror("Unexpected Token");
    }
    tok->next = new_token(NULL, TK_EOF);
    return(head.next);
}
