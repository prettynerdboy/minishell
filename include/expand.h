/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 03:28:08 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:25:36 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "minishell.h"
# include "struct.h"

char	*ft_strjoin_free(char *s1, char *s2);
char	*expand_env_var(char *str, int *i);
char	*process_single_quote(char *str, int *i);
char	*handle_dollar_in_dquote(char *str, int *i, char *result);
char	*handle_char_in_dquote(char *str, int *i, char *result);
char	*process_double_quote(char *str, int *i);
char	*expand_word(char *word);
void	expand_tokens(t_token *tokens);
#endif