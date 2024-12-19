/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:18:52 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 04:08:43 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATHNAME_SIZE 512

int	ft_cd(char **argv)
{
	char *oldpwd;
	char *home;
	char pathname[PATHNAME_SIZE];
	t_map **envmap;

	ft_memset(pathname, '\0', PATHNAME_SIZE);
	envmap = get_envmap();
	oldpwd = xgetenv("OLDPWD");
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		if (!oldpwd)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (1);
		}
		map_set(*envmap, "OLDPWD", xgetenv("PWD"));
		if (chdir(oldpwd) == -1)
		{
			perror("cd");
			return (1);
		}
		getcwd(pathname, PATHNAME_SIZE);
		map_set(*envmap, "PWD", pathname);
		return (0);
	}
	if (argv[1] && argv[1][0] == '.' && argv[1][1] == '.')
	{
		if (chdir("..") == -1)
		{
			if (chdir(oldpwd) == -1)
			{
				perror("cd");
				return (1);
			}
		}
		getcwd(pathname, PATHNAME_SIZE);
		map_set(*envmap, "PWD", pathname);
		return (0);
	}
	if (!argv[1])
	{
		home = xgetenv("HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
		map_set(*envmap, "OLDPWD", xgetenv("PWD"));
		map_set(*envmap, "PWD", home);
		return (chdir(home));
	}
	map_set(*envmap, "OLDPWD", xgetenv("PWD"));
	if (chdir(argv[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	getcwd(pathname, PATHNAME_SIZE);
	map_set(*envmap, "PWD", pathname);
	return (0);
}