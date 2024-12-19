#include "minishell.h"

static bool	check_pipe_error(t_token *current)
{
	if (!current->next || current->next->type == TK_EOF)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return (false);
	}
	if (token_is(current->next, "|"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	is_redirect_token(t_token *token)
{
	return (token_is(token, ">") || token_is(token, "<") || token_is(token,
			">>") || token_is(token, "<<"));
}

static bool	check_redirect_filename_error(t_token *current)
{
	if (!current->next || current->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	check_consecutive_redirect_error(t_token *current)
{
	if (is_redirect_token(current) && is_redirect_token(current->next))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `\n",
			STDERR_FILENO);
		ft_putstr_fd(current->next->word, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	check_syntax_error(t_token *tokens)
{
	t_token	*current;
	int		token_count;

	token_count = get_token_list_length(tokens);
	if (token_count > MAX_TOKENS)
	{//↓構文のエラーチェック
		ft_eprintf("minishell: too many input\n");
		return (false);
	}
	current = tokens;
	while (current && current->type != TK_EOF)
	{
		if (token_is(current, "|") && !check_pipe_error(current))
			return (false);
		if (is_redirect_token(current)
			&& !check_redirect_filename_error(current))
			return (false);
		if (!check_consecutive_redirect_error(current))
			return (false);
		current = current->next;
	}
	return (true);
}
