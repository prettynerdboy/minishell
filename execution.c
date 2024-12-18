#include "minishell.h"
#include <dirent.h>
#include <errno.h>

static char	*find_cmd_path(char **path_arr, const char *cmd)
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
	dprintf(2, "%s command not found\n", cmd);
	return (NULL);
}

static char	*check_path(const char *cmd)
{
	DIR	*dirp;

	if (!cmd)
		return (NULL);
	dirp = opendir(cmd);
	if (dirp)
	{
		dprintf(2, "%s : Is a directory\n", cmd);
		closedir(dirp);
		return (NULL);
	}
	closedir(dirp);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	dprintf(2, "%s : No such file or directory\n", cmd);
	return (NULL);
}

static char	*make_path(const char *cmd)
{
	char	**path_arr;
	char	*path_env;
	char	*path;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (check_path(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_arr = ft_split(path_env, ':');
	if (!path_arr)
		return (NULL);
	path = find_cmd_path(path_arr, cmd);
	wp_free(&path_arr);
	return (path);
}

static void	init_pipe(t_node *node)
{
	if (pipe(node->outpipe) < 0)
		perror("pipe");
	node->next->inpipe[READ] = node->outpipe[READ];
	node->next->inpipe[WRITE] = node->outpipe[WRITE];
}

static void	connect_pipe(t_node *node)
{
	if (node->inpipe[READ] != STDIN_FILENO)
	{
		dup2(node->inpipe[READ], STDIN_FILENO);
		close(node->inpipe[READ]);
	}
	if (node->outpipe[WRITE] != STDOUT_FILENO)
	{
		dup2(node->outpipe[WRITE], STDOUT_FILENO);
		close(node->outpipe[WRITE]);
	}
	if (node->inpipe[WRITE] != STDOUT_FILENO)
		close(node->inpipe[WRITE]);
	if (node->outpipe[READ] != STDIN_FILENO)
		close(node->outpipe[READ]);
}

char	**token_to_argv(t_token *tok)
{
	int		list_len;
	char	**argv;
	int		i;

	list_len = get_token_list_length(tok);
	argv = malloc((list_len + 1) * sizeof(char *));
	if (argv == NULL)
		perror("malloc");
	i = 0;
	while (tok != NULL && tok->type != TK_EOF)
	{
		argv[i] = ft_strdup(tok->word);
		if (argv[i] == NULL)
		{
			wp_free(&argv);
			perror("strdup");
		}
		i++;
		tok = tok->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

pid_t	run_pipeline(t_data *data)
{
	t_node		*current_node;
	extern char	**environ;
	char		*cmd;
	char		*path;
	pid_t		pid;
	char		**argv;
	int			status;

	if (data == NULL || data->nodes == NULL)
		return (-1);
	current_node = data->nodes;
	while (current_node != NULL)
	{
		if (current_node && current_node->next)
			init_pipe(current_node);
		if (!current_node->next)
		{
			// ビルトインコマンドの実行
			status = execute_builtin(current_node->command);
			if (status != -1) // ビルトインコマンドが実行された場合
			{
				*get_status() = status;
				return (0);
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (-1);
		}
		else if (pid == 0)
		{ //小プロのエラー時に、エラー起きたらノードとか全部フリー
			signal(SIGQUIT, SIG_DFL);
			argv = token_to_argv(current_node->command->args);
			cmd = argv[0];
			connect_pipe(current_node);
			if (redirect(current_node->command->redirects) != 0)
			{
				wp_free(&argv);
				exit_with_status(data, 1);
			}
			close_redirect_fds(current_node);
			if (!cmd || check_builtin(cmd))
			{
				wp_free(&argv);
				exit_with_status(data, 0);//これのexitstatusあってる？
			}
			path = make_path(cmd);
			if (!path)
			{
				wp_free(&argv);
				exit_with_status(data, 127);
			}
			if (access(path, X_OK) != 0)
			{
				dprintf(2,"%s :Permission denied\n",path);
				wp_free(&argv);
				exit_with_status(data, 126);
			}
			execve(path, argv, environ);
			free(path);
			wp_free(&argv);
			perror("execve");
			exit_with_status(data, EXIT_FAILURE);
		}
		if (current_node->inpipe[0] != STDIN_FILENO)
			close(current_node->inpipe[0]);
		if (current_node->next)
			close(current_node->outpipe[1]);
		// close_pipe_fds(current_node);
		// wp_free(&argv);
		if (pid > 0)
			close_redirect_fds(current_node->command);
		current_node = current_node->next;
	}
	return (pid);
}

int	wait_process(pid_t last_pid)
{
	int		status;
	pid_t	child_pid;
	int		child_status;

	status = 0;
	child_status = 0;
	signal(SIGINT, SIG_IGN);
	while ((child_pid = wait(&child_status)) > 0)
	{
		if (child_pid == last_pid)
			status = WEXITSTATUS(child_status);
	}
	if (child_pid == -1 && errno != ECHILD)
	{
		perror("wait");
		printf("\n");
	}
	if (WTERMSIG(child_status) == SIGQUIT)
	{
		printf("core dump\n");
		status = SIGQUIT_STATUS;
	}
	else if (WTERMSIG(child_status) == SIGINT)
	{
		printf("\n");
		status = SIGINT_STATUS;
	}
	// dprintf(2, "signal status: %d, child_status: %d, child_pid: %d, coredump status:%d\n",
	// 	WTERMSIG(child_status), child_status, child_pid, status);
	// fflush(0);
	signal(SIGINT, &signal_handler);
	return (status);
}

int	execution(t_data *data)
{
	int		status;
	pid_t	pid;

	pid = run_pipeline(data);
	status = wait_process(pid);
	return (status);
}
