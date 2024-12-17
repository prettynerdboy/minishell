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
// リダイレクトなしの場合の実行関数
static int	execute_builtin_simple(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(argv));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(argv));
	return (-1);
}

// リダイレクトありの場合の実行関数
static int	handle_builtin_redirect(t_node *cmd_node,
		int (*builtin_func)(char **))
{
	int		original_stdout;
	int		original_stdin;
	int		status;
	char	**argv;

	// 標準入出力をバックアップ
	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	// リダイレクトの設定
	if (cmd_node->redirects && redirect(cmd_node->redirects) != 0)
	{
		close(original_stdout);
		close(original_stdin);
		return (1);
	}
	// コマンドライン引数の準備
	argv = token_to_argv(cmd_node->args);
	if (!argv)
	{
		close(original_stdout);
		close(original_stdin);
		return (1);
	}
	// ビルトインコマンドの実行
	status = builtin_func(argv);
	// 標準入出力を元に戻す
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
	wp_free(&argv);
	return (status);
}

// メインの実行関数
int	execute_builtin(t_node *cmd_node)
{
	char **argv;
	int status;

	if (!cmd_node || !cmd_node->args)
		return (-1);

	// リダイレクトの有無で処理を分岐
	if (cmd_node->redirects)
	{
		argv = token_to_argv(cmd_node->args);
		if (!argv)
			return (1);

		if (ft_strcmp(argv[0], "echo") == 0)
			status = handle_builtin_redirect(cmd_node, ft_echo);
		else if (ft_strcmp(argv[0], "cd") == 0)
			status = handle_builtin_redirect(cmd_node, ft_cd);
		else if (ft_strcmp(argv[0], "pwd") == 0)
			status = handle_builtin_redirect(cmd_node, ft_pwd);
		else if (ft_strcmp(argv[0], "export") == 0)
			status = handle_builtin_redirect(cmd_node, ft_export);
		else if (ft_strcmp(argv[0], "unset") == 0)
			status = handle_builtin_redirect(cmd_node, ft_unset);
		else if (ft_strcmp(argv[0], "env") == 0)
			status = handle_builtin_redirect(cmd_node, ft_env);
		else if (ft_strcmp(argv[0], "exit") == 0)
			status = handle_builtin_redirect(cmd_node, ft_exit);
		else
			status = -1;

		wp_free(&argv);
		return (status);
	}
	else
	{
		// リダイレクトがない場合は直接実行
		argv = token_to_argv(cmd_node->args);
		if (!argv)
			return (1);

		status = execute_builtin_simple(argv);
		wp_free(&argv);
		return (status);
	}
}