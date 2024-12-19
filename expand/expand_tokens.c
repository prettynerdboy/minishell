/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 03:28:32 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:18:31 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	check_trim(t_token *current, char trim_word)
{
	char	*unquoted;
	char	*tmp;

	tmp = NULL;
	unquoted = NULL;
	if (trim_word == '\'')
		tmp = "\'";
	else if (trim_word == '\"')
		tmp = "\"";
	if (!tmp)
		return ;
	unquoted = ft_strtrim(current->word, tmp);
	free(current->word);
	current->word = unquoted;
}

void	expand_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;
	char	*expanded;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (prev && token_is(prev, "<<"))
		{
			check_trim(current, current->word[0]);
			prev = current;
			current = current->next;
			continue ;
		}
		if (current->type == TK_WORD)
		{
			expanded = expand_word(current->word);
			free(current->word);
			current->word = expanded;
		}
		prev = current;
		current = current->next;
	}
}
