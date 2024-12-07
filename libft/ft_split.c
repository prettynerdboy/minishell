/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:40:24 by anakin            #+#    #+#             */
/*   Updated: 2024/08/22 16:02:37 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(const char *str, char c)
{
	int	len;
	int	sflag;

	len = 0;
	sflag = 0;
	while (*str)
	{
		if (*str != c && !sflag)
		{
			sflag = 1;
			len++;
		}
		else if (*str == c)
		{
			sflag = 0;
		}
		str++;
	}
	return (len);
}

static char	*get_memory(char *str, char c)
{
	while (*str && (*str != c))
		++str;
	return (str);
}

static char	**check_str(const char *s, char c)
{
	char	**r;

	r = (char **)ft_calloc(get_len(s, c) + 1, sizeof(char *));
	if (!s || r == NULL)
		return (NULL);
	return (r);
}

static char	**free_all(char **r, int i)
{
	int	a;

	a = 0;
	while (a <= i)
		free(r[a++]);
	free(r);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	int		i;
	char	*from;

	r = check_str(s, c);
	if (!r)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			from = (char *)s;
			s = get_memory((char *)s, c);
			r[i] = (char *)ft_calloc((char *)s - from + 1, sizeof(char));
			if (r[i] == NULL)
				return (free_all(r, i));
			ft_strlcpy(r[i++], from, (char *)s - from + 1);
			if (*s == 0)
				break ;
		}
		s++;
	}
	return (r);
}

// #include <stdio.h>

// int main(void)
// {
//     char split='b';
//     char str[30]="AAAbbBBbbCC";
// 	char **result;
// 	int i;
// 	result = ft_split(str, split);
// 	i=0;

// while(result[i])
//     {
// 		printf("%s\n",result[i]);
// 		i++;
// 	}

// i = 0;
// 	while(result[i])
// 		free(result[i++]);
// 	free(result);

// return (0);
// }

//一次元の配列の長さと二次元配列の両方の長さを把握する必要がある。
//二次元配列の中にどうやって格納するか