/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 03:48:43 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 05:25:06 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "expand.h"
# include "redirect.h"
# include "struct.h"

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
t_token	*new_token(char *word, t_token_type type);
int		is_blank(char c);
int		is_meta(char c);
int		is_word(char c);
t_token	*tokencpy(t_token *tok);
int		check_eof(t_token *tok);
void	add_token(t_token **tok, t_token *elm);
int		token_is(t_token *token, const char *str);
int		get_token_list_length(t_token *tok);

// tokenizefunction
t_token	*operator(char **rest, char *line);
bool	handle_quote(char **line, char quote_type, t_quote_state *quote);
t_token	*word(char **rest, char *line);
t_token	*tokenizer(char *line);

// checksyntax
bool	check_syntax_error(t_token *tokens);

// node
t_node	*new_node(t_node_kind kind);
void	add_node(t_node **node, t_node *elm);
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);
t_node	*make_cmd_node(t_token **rest, t_token *tok);
t_node	*pipeline(t_token **rest, t_token *tok);
t_node	*parser(t_token *tok);

// signal
void	signal_handler(int sig);
void	reset_prompt(void);
void	child_signal_handler(int sig);

// exev
int		execution(t_data *data);
pid_t	run_pipeline(t_data *data);
char	**token_to_argv(t_token *tok);
int		wait_process(pid_t last_pid);

// free
void	wp_free(char ***str);
void	error_exit(char *msg);
void	free_token_list(t_token **head);
void	free_node(t_node **node);
void	free_data(t_data **data);
void	exit_with_status(t_data *data, int status);
void	free_envmap(void);

// map
t_item	*item_new(char *name, char *value);
char	*item_get_string(t_item *item);
t_map	*map_new(void);
char	*map_get(t_map *map, const char *name);
int		map_put(t_map *map, const char *string, bool allow_empty_value);
int		map_set(t_map *map, const char *name, const char *value);
int		map_unset(t_map *map, const char *name);
size_t	map_len(t_map *map, bool count_null_value);
void	map_initialize(t_map *map, char *string);

// environment.c
char	*xgetenv(const char *name);
void	initenv(void);
char	**get_environ(t_map *map);

// status
int		*get_status(void);
t_data	*get_data(void);
t_map	**get_envmap(void);
int		**heredoc_fds(void);
int		*is_pipe_heredoc(void);
int		*is_run_heredoc(void);
// builtin
int		ft_export(char **argv);
int		ft_unset(char **argv);
int		ft_env(char **argv);
int		ft_echo(char **argv);
int		ft_cd(char **argv);
int		ft_pwd(char **argv);
int		ft_exit(char **argv);
int		execute_builtin(t_node *cmd_node);

#endif
