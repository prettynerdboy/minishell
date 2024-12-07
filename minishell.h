#ifndef MINISHELL_H
# define MINISHELL_H
#include <readline/readline.h>
#include <string.h> //delete
# include "libft.h"

//struct
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

enum e_node_kind {
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
}; typedef enum e_node_kind		t_node_kind;

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

//macro
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

//function

//token_utility
t_token	*new_token(char *word, t_token_type type);
int is_blank(char c);
int is_meta(char c);
int	is_word(char c);
t_token	*tokencpy(t_token *tok);
int check_eof(t_token *tok);
void	add_token(t_token **tok, t_token *elm);
int token_is(t_token *token, const char *str);

//tokenizefunction
t_token *operator(char **rest, char *line);
void handle_quote(char **line, char quote_type);
t_token *word(char **rest, char *line);
t_token *tokenizer(char *line);

//node
t_node	*new_node(t_node_kind kind);
void	add_node(t_node **node, t_node *elm);
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node *make_cmd_node(t_token **rest, t_token *tok);
t_node	*pipeline(t_token **rest, t_token *tok);
t_node	*parser(t_token *tok);




#endif