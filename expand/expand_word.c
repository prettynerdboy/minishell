/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 03:27:12 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:34:08 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*ft_strjoin_free(char *s1, char *s2)
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

char	*expand_word(char *word)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			tmp = process_single_quote(word, &i);
		else if (word[i] == '"')
			tmp = process_double_quote(word, &i);
		else if (word[i] == '$')
			tmp = expand_env_var(word, &i);
		else
		{
			tmp = ft_substr(word, i, 1);
			i++;
		}
		result = ft_strjoin_free(result, tmp);
		free(tmp);
	}
	return (result);
}

// void	expand_tokens(t_token *tokens)
// {
// 	t_token *current;
// 	char *expanded;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == TK_WORD)
// 		{
// 			expanded = expand_word(current->word);
// 			free(current->word);
// 			current->word = expanded;
// 		}
// 		current = current->next;
// 	}
// }
