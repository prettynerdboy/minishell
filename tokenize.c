#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>


# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

//This tokenizer is beta that doesn't handle error handling properly, edge cases either.

enum e_token_type {
	TK_WORD,
	TK_OP,
	TK_EOF,
};typedef enum e_token_type	t_token_type;

struct s_token {
	char			*word;
	t_token_type	type;
	struct s_token			*next;
}; typedef struct s_token		t_token;

t_token	*new_token(char *word, t_token_type type)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		perror("calloc error");
	tok->word = word;
	tok->type = type;
	return (tok);
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
	if (is_blank(c) || (c && strchr("|<>\n", c)))
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
        op_len = strlen(operators[i]);
        if (strncmp(line, operators[i], op_len) == 0)
        {
            op = strdup(operators[i]);
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
    word = strndup(start, line - start);
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


// void print_tokens(t_token *tokens) {
//     while (tokens) {
//         const char *kind_str = tokens->type == TK_WORD ? "WORD" :
//                                tokens->type == TK_OP   ? "OP" :
//                                                           "EOF";
//         printf("Token: %s (Kind: %s)\n", tokens->word ? tokens->word : "NULL", kind_str);
//         tokens = tokens->next;
//     }
// }
// int main(void) {
//     char *line;
//     t_token *token;

//     while (1) {
//         line = readline("tokenizer> ");
//         printf("comandline=%s\n",line);
//         add_history(line);
//         token = tokenizer(line);
//         print_tokens(token);
//         // free_tokens(token);
//         free(line);
//     }
//     return 0;
// }