#include "minishell.h"
#include <dirent.h>
#include <errno.h>

pid_t	run_pipeline(t_data *data)
{
	t_node		*current_node;
	extern char	**environ;
	char		*cmd;
	char		*path;
	pid_t		pid;
	char		**argv;
	int			status;
	int			redirect_status;
	int			builtin_status;

	if (data == NULL || data->nodes == NULL)
		return (-1);
	current_node = data->nodes;
	if (!current_node->next)
	{
		builtin_status = run_parent_builtin(current_node);
		if (builtin_status != 1)
		{
			*get_status() = builtin_status;
			return (-1);
		}
	}
	while (current_node != NULL)
	{
		if (current_node && current_node->next)
			init_pipe(current_node);
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
			if (!argv)
				exit_with_status(data, EXIT_FAILURE);
			cmd = argv[0];
			// ビルトインコマンドの場合
			connect_pipe(current_node);
			if (check_builtin(cmd))
			{
				status = execute_builtin(current_node->command);
				ft_eprintf("status: %d\n", status);
				wp_free(&argv);
				exit_with_status(data, status);
			}
			redirect_status = redirect(current_node->command->redirects);
			if (redirect_status != 0)
			{
				if (redirect_status != 130)
					ft_eprintf("%s : No such file or directory\n",
						current_node->command->redirects->filename->word);
				wp_free(&argv);
				exit_with_status(data, redirect_status);
			}
			close_redirect_fds(current_node);
			path = make_path(cmd);
			if (!path)
			{
				wp_free(&argv);
				exit_with_status(data, 127);
			}
			if (access(path, X_OK) != 0)
			{
				ft_eprintf("%s :Permission denied\n", path);
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
		if (pid > 0)
			close_redirect_fds(current_node->command);
		current_node = current_node->next;
	}
	return (pid);
}

int	execution(t_data *data)
{
	int		status;
	pid_t	pid;

	pid = run_pipeline(data);
	if (pid > 0)
	{
		status = wait_process(pid);
		return (status);
	}
	else
		return (-1);
}
