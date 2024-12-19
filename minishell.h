#ifndef MINISHELL_H
# define MINISHELL_H
# include "./ft_eprintf/ft_eprintf.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h> //for mac
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// struct
enum						e_token_type
{
	TK_WORD,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_type	t_token_type;

struct						s_token
{
	char					*word;
	t_token_type			type;
	struct s_token			*next;
};
typedef struct s_token		t_token;

typedef struct s_quote_state
{
	bool					in_single_quote;
	bool					in_double_quote;
}							t_quote_state;

enum						e_node_kind
{
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
};
typedef enum e_node_kind	t_node_kind;

struct						s_node
{
	t_node_kind				kind;
	struct s_node			*command;
	struct s_node			*redirects;
	t_token					*args;
	t_token					*filename;
	t_token					*delimiter;
	int						default_fd;
	int						redirect_fd;
	int						inpipe[2];
	int						outpipe[2];
	struct s_node			*next;
};
typedef struct s_node		t_node;

// 必要な構造体の宣言
typedef struct s_data
{
	t_token					*tokens;
	t_node					*nodes;
}							t_data;

typedef struct s_map		t_map;
typedef struct s_env_item	t_item;

struct						s_env_item
{
	char					*name;
	char					*value;
	t_item					*next;
};

struct						s_map
{
	t_item					item_head;
};

typedef int					(*t_builtin_func)(char **argv);

typedef struct s_builtin
{
	char					*name;
	t_builtin_func			func;
}							t_builtin;

// macro
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'
# define READ 0
# define WRITE 1
# define SIGINT_STATUS 130
# define SIGQUIT_STATUS 131
# define TOKEN_PARSE_ERROR_STATUS 258
# define MAX_TOKENS 100
// function

// token_utility
t_token						*new_token(char *word, t_token_type type);
int							is_blank(char c);
int							is_meta(char c);
int							is_word(char c);
t_token						*tokencpy(t_token *tok);
int							check_eof(t_token *tok);
void						add_token(t_token **tok, t_token *elm);
int							token_is(t_token *token, const char *str);
int							get_token_list_length(t_token *tok);

// tokenizefunction
t_token						*operator(char **rest, char *line);
bool						handle_quote(char **line, char quote_type,
								t_quote_state *quote);
t_token						*word(char **rest, char *line);
t_token						*tokenizer(char *line);

// checksyntax
bool						check_syntax_error(t_token *tokens);

// expand
void						expand_tokens(t_token *tokens);

// node
t_node						*new_node(t_node_kind kind);
void						add_node(t_node **node, t_node *elm);
t_node						*redirect_out(t_token **rest, t_token *tok);
t_node						*redirect_in(t_token **rest, t_token *tok);
t_node						*redirect_append(t_token **rest, t_token *tok);
t_node						*redirect_heredoc(t_token **rest, t_token *tok);
t_node						*make_cmd_node(t_token **rest, t_token *tok);
t_node						*pipeline(t_token **rest, t_token *tok);
t_node						*parser(t_token *tok);

// signal
void						signal_handler(int sig);
void						reset_prompt(void);
void						child_signal_handler(int sig);
// redirect
int							open_redir_file(t_node *node);
int							handle_redirection(t_node *node);
int							redirect(t_node *redir);
void						close_redirect_fds(t_node *node);
int							handle_heredoc(t_node *redirect_node);

// exev
int							execution(t_data *data);
pid_t						run_pipeline(t_data *data);
char						**token_to_argv(t_token *tok);
int							wait_process(pid_t last_pid);

// free
void						wp_free(char ***str);
void						error_exit(char *msg);
void						free_token_list(t_token **head);
void						free_node(t_node **node);
void						free_data(t_data **data);
void						exit_with_status(t_data *data, int status);
void						free_envmap(void);

// map
t_item						*item_new(char *name, char *value);
char						*item_get_string(t_item *item);
t_map						*map_new(void);
char						*map_get(t_map *map, const char *name);
int							map_put(t_map *map, const char *string,
								bool allow_empty_value);
int							map_set(t_map *map, const char *name,
								const char *value);
int							map_unset(t_map *map, const char *name);
size_t						map_len(t_map *map, bool count_null_value);
void						map_initialize(t_map *map, char *string);

// environment.c
char						*xgetenv(const char *name);
void						initenv(void);
char						**get_environ(t_map *map);

// status
int							*get_status(void);
t_data						*get_data(void);
t_map						**get_envmap(void);
int							**heredoc_fds(void);
int							*is_pipe_heredoc(void);
int							*is_run_heredoc(void);
// builtin
int							ft_export(char **argv);
int							ft_unset(char **argv);
int							ft_env(char **argv);
int							ft_echo(char **argv);
int							ft_cd(char **argv);
int							ft_pwd(char **argv);
int							ft_exit(char **argv);
int							execute_builtin(t_node *cmd_node);

#endif
