#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

enum e_token_kind {
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_kind		t_token_kind;

enum e_node_kind {
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
};
typedef enum e_node_kind		t_node_kind;

struct s_token {
	char			*word;
	t_token_kind	kind;
	struct s_token			*next;
};typedef struct s_token			t_token;

struct s_node {
	t_node_kind	kind;
	struct s_node	*next;

	t_token		*args;
	struct s_node		*redirects;

	int			targetfd;
	t_token		*filename;
	t_token		*delimiter;
	int			filefd;
	int			stashed_targetfd;

	int			inpipe[2];
	int			outpipe[2];
	struct s_node		*command;
}; typedef struct s_node			t_node;


t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

t_token	*tokencpy(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	return (new_token(word, tok->kind));
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
int check_eof(t_token *tok)
{
	if(tok->kind == TK_EOF)
		return (1);
	else
		return(0);
}

int token_is(t_token *token, const char *str)
{
    size_t i;
	i=0;
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

	node = calloc(1, sizeof(*node));
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

t_node *make_cmd_node(t_token **rest, t_token *tok)
{
    t_node *node;

    node = new_node(ND_SIMPLE_CMD);
    while (tok && !check_eof(tok) && !token_is(tok,"|") && !token_is(tok,"\n"))
    {
        if (tok->kind == TK_WORD)
        {
            add_token(&node->args, tokencpy(tok));
            tok = tok->next;
        }
        else if (token_is(tok, ">") && tok->next && tok->next->kind == TK_WORD)
        	add_node(&node->redirects, redirect_out(&tok, tok));
        else if (token_is(tok, "<") && tok->next && tok->next->kind == TK_WORD)
            add_node(&node->redirects, redirect_in(&tok, tok));
		//add other redirect
        else
            perror("parse,error");
    }
    *rest = tok;
    return node;
}

t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_node	*node;

	if (!tok || tok->kind == TK_EOF)
    {
        *rest = tok;
        return NULL;
    }
	node = new_node(ND_PIPELINE);
	memset(node->inpipe, -1, sizeof(node->inpipe)); 
    memset(node->outpipe, -1, sizeof(node->outpipe));
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


//test↓
t_token *create_token_list(char **words, t_token_kind *kinds, size_t count)
{
    t_token *head = NULL;
    t_token *current = NULL;

    for (size_t i = 0; i < count; i++)
    {
        t_token *new_tok = new_token(words[i], kinds[i]);
        if (!head)
        {
            head = new_tok;
            current = head;
        }
        else
        {
            current->next = new_tok;
            current = current->next;
        }
    }
    return head;
}
int main()
{
    char *words[] = {"echo", "hello", ">", "output.txt", "|", "cat", "output.txt", NULL};
    t_token_kind kinds[] = {TK_WORD, TK_WORD, TK_OP, TK_WORD, TK_OP, TK_WORD, TK_WORD, TK_EOF};
    t_token *tokens = create_token_list(words, kinds, 8);
    t_node *tree = parser(tokens);
    printf("Parsed tree:\n");
    t_node *current_pipeline = tree;
    while (current_pipeline)
    {
        printf("Pipeline:\n");

        t_node *cmd = current_pipeline->command;
        while (cmd)
        {
            if (cmd->kind == ND_SIMPLE_CMD)
            {
                printf("  Command:\n");

                t_token *arg = cmd->args;
                while (arg)
                {
                    printf("    Arg: %s\n", arg->word);
                    arg = arg->next;
                }

                t_node *redir = cmd->redirects;
                while (redir)
                {
                    printf("    Redirect: %s\n", redir->filename->word);
                    redir = redir->next;
                }
            }
            cmd = cmd->next;
        }
        current_pipeline = current_pipeline->next;
    }
    return 0;
}
