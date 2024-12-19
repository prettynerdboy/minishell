/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:20:47 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:23:43 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../ft_eprintf/ft_eprintf.h"
# include "../libft/libft.h"
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

typedef struct s_token
{
	char					*word;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

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

#endif