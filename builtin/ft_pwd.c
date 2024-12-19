/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:19:14 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/19 11:04:31 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

int	ft_pwd(char **argv)
{
	char	*cwd;

	(void)argv;
	cwd = xgetenv("PWD");
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	// free(cwd);
	return (0);
}
