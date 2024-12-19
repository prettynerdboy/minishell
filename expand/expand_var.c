/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 03:31:59 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:18:28 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

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

char	*expand_env_var(char *str, int *i)
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
