#include "minishell.h"

// builtin.h
typedef int			(*t_builtin_func)(char **argv);

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

int	ft_pwd(char **argv)
{
	char	*cwd;

	(void)argv;
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

int	ft_export(char **argv)
{
	int			i;
	char		*equal_sign;
	extern char	**environ;
	char		**sorted_env;

	i = 0;
	if (!argv[1])
	{
		// 環境変数を表示（ソートされた順で）
		sorted_env = environ;
		// ここでソート処理を行う
		while (sorted_env[i])
		{
			printf("declare -x %s\n", sorted_env[i]);
			i++;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		equal_sign = ft_strchr(argv[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (setenv(argv[i], equal_sign + 1, 1) == -1)
			{
				perror("export");
				return (1);
			}
			*equal_sign = '=';
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (unsetenv(argv[i]) == -1)
		{
			perror("unset");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_env(char **argv)
{
	extern char	**environ;
	int			i;

	if (argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

int	ft_exit(char **argv)
{
	int		status;
	t_data	*data;

	data = get_data();
	if (!argv[1])
	{
		free_token_list(&data->tokens);
		free_node(data->nodes);
		printf("exit\n");
		exit(0);
	}
	status = ft_atoi(argv[1]);
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	free_token_list(&data->tokens);
	free_node(data->nodes);
	printf("exit\n");
	exit(status);
}

// ビルトインコマンドの実行関数
int	execute_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
	return (-1); // ビルトインコマンドが見つからない場合
}