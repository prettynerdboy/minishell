#include "minishell.h"
#include <errno.h>

void	wp_free(char ***str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
}

void	error_exit(char *msg)
{
	const char	*red = "\033[31m";
	const char	*reset = "\033[0m";

	write(2, red, 5);
	ft_putendl_fd(msg, 2);
	write(2, reset, 4);
	exit(EXIT_FAILURE);
}
static char	*find_path(char **path_arr, const char *cmd)
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
	return (NULL);
}

static char	*make_path(const char *cmd)
{
	char	**path_arr;
	char	*path_env;
	char	*path;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_arr = ft_split(path_env, ':');
	if (!path_arr)
		return (NULL);
	path = find_path(path_arr, cmd);
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
	close(node->outpipe[READ]);
	dup2(node->inpipe[READ], STDIN_FILENO);
	if (node->inpipe[READ] != STDIN_FILENO)
		close(node->inpipe[READ]);
	dup2(node->outpipe[WRITE], STDOUT_FILENO);
	if (node->outpipe[WRITE] != STDOUT_FILENO)
		close(node->outpipe[WRITE]);
}

static char	**token_to_argv(t_token *tok)
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
		argv[i] = strdup(tok->word);
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

pid_t	run_pipeline(t_node *node)
{
	t_node		*current_node;
	extern char	**environ;
	char		*cmd;
	char		*path;
	pid_t		pid;
	char		**argv;

	if (node == NULL)
		return (-1);
	current_node = node;
	while (current_node != NULL)
	{
		if (current_node && current_node->next)
			init_pipe(current_node);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			connect_pipe(current_node);
			argv = token_to_argv(current_node->command->args);
			cmd = argv[0];
			path = make_path(cmd);
			if (!path)
				perror("command not found");
			execve(path, argv, environ);
			perror("execve");
		}
		if (current_node->inpipe[0] != STDIN_FILENO)
			close(current_node->inpipe[0]);
		if (current_node->next)
			close(current_node->outpipe[1]);
		current_node = current_node->next;
	}
	return (pid);
}

int	wait_process(pid_t last_pid)
{
	pid_t	child_pid;
	int		status;
	int		child_status;

	status = 0;
	while ((child_pid = wait(&child_status)) > 0)
	{
		if (child_pid == last_pid)
			status = WEXITSTATUS(child_status);
	}
	if (child_pid == -1 && errno != ECHILD)
		perror("wait");
	return (status);
}

int	execution(t_node *node)
{
	pid_t	pid;
	int		status;

	pid = run_pipeline(node);
	status = wait_process(pid);
	return (status);
}
