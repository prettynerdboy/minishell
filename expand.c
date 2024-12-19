#include "minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static char	*handle_status_var(int *i)
{
	int		*status;
	char	*var_value;

	status = get_status();
	var_value = ft_itoa(*status);
	(*i)++;
	return (var_value);
}

static char	*get_var_name(char *str, int *i, int start)
{
	int		len;
	char	*var_name;

	len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		len++;
		(*i)++;
	}
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	return (var_name);
}

static char	*expand_env_var(char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = *i + 1;
	(*i)++;
	if (str[*i] == '?')
		return (handle_status_var(i));
	var_name = get_var_name(str, i, start);
	if (!var_name)
		return (ft_strdup("$"));
	var_value = xgetenv(var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

static char	*process_single_quote(char *str, int *i)
{
	int	start;
	int	len;

	start = *i + 1;
	len = 0;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, len));
}

static char	*handle_dollar_in_dquote(char *str, int *i, char *result)
{
	char	*tmp;

	tmp = expand_env_var(str, i);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	return (result);
}

static char	*handle_char_in_dquote(char *str, int *i, char *result)
{
	char	*tmp;

	tmp = ft_substr(str, *i, 1);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	(*i)++;
	return (result);
}

static char	*process_double_quote(char *str, int *i)
{
	char	*result;

	result = ft_strdup("");
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			result = handle_dollar_in_dquote(str, i, result);
		else if (str[*i] == '\'')
			result = handle_char_in_dquote(str, i, result);
		else
			result = handle_char_in_dquote(str, i, result);
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

static char	*expand_word(char *word)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			tmp = process_single_quote(word, &i);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
		}
		else if (word[i] == '"')
		{
			tmp = process_double_quote(word, &i);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
		}
		else if (word[i] == '$')
		{
			tmp = expand_env_var(word, &i);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_substr(word, i, 1);
			result = ft_strjoin_free(result, tmp);
			free(tmp);
			i++;
		}
	}
	return (result);
}

void	expand_tokens(t_token *tokens)
{
	t_token *current;
	char *expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TK_WORD)
		{
			expanded = expand_word(current->word);
			free(current->word);
			current->word = expanded;
		}
		current = current->next;
	}
}