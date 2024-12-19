/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 03:30:43 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:18:33 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*handle_dollar_in_dquote(char *str, int *i, char *result)
{
	char	*tmp;

	tmp = expand_env_var(str, i);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	return (result);
}

char	*handle_char_in_dquote(char *str, int *i, char *result)
{
	char	*tmp;

	tmp = ft_substr(str, *i, 1);
	result = ft_strjoin_free(result, tmp);
	free(tmp);
	(*i)++;
	return (result);
}

char	*process_single_quote(char *str, int *i)
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

char	*process_double_quote(char *str, int *i)
{
	char *result;

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