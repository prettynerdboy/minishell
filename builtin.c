#include "minishell.h"

// builtin.h
typedef int			(*t_builtin_func)(char **args);

typedef struct s_builtin
{
	char			*name;
	t_builtin_func	func;
}					t_builtin;

// builtin.c
int	ft_echo(char **argv)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	ft_cd(char **argv)
{
	char	*home;

	if (!argv[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
		return (chdir(home));
	}
	if (chdir(argv[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

// ビルトインコマンドの実行関数
int	execute_builtin(char **args)
{
	t_builtin builtins[] = {{"echo", ft_echo},
							{"cd", ft_cd},
							{"pwd", ft_pwd},
							// 他のビルトインコマンドも同様に追加
							{NULL, NULL}};
	int i;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args));
		i++;
	}
	return (-1); // ビルトインコマンドが見つからない場合
}