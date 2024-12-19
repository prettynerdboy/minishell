#include "minishell.h"
#include <dirent.h>

char	*find_cmd_path(char **path_arr, const char *cmd)
{
	char	*part_path;
	char	*full_path;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		part_path = ft_strjoin(path_arr[i], "/");
		if (!part_path)
			return (NULL);
		full_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_eprintf("%s : command not found\n", cmd);
	return (NULL);
}

char	*check_path(const char *cmd)
{
	DIR	*dirp;

	if (!cmd)
		return (NULL);
	dirp = opendir(cmd);
	if (dirp)
	{
		ft_eprintf("%s : Is a directory\n", cmd);
		closedir(dirp);
		return (NULL);
	}
	closedir(dirp);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	ft_eprintf("%s : No such file or directory\n", cmd);
	return (NULL);
}

char	*make_path(const char *cmd)
{
	char	**path_arr;
	char	*path_env;
	char	*path;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (check_path(cmd));
	path_env = xgetenv("PATH");
	if (!path_env)
	{
		ft_eprintf("%s: No such file or directory\n", cmd);
		return (NULL);
	}
	path_arr = ft_split(path_env, ':');
	if (!path_arr)
		return (NULL);
	path = find_cmd_path(path_arr, cmd);
	wp_free(&path_arr);
	return (path);
}
