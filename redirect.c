#include "minishell.h"

int	handle_heredoc(t_node *redirect_node)
{
	int		fd[2];
	char	*line;
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
	{
		perror("Failed to create pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0) // 子プロセス
	{
		*heredoc_fds() = fd;
		signal(SIGINT, child_signal_handler);
		line = NULL;
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(fd[WRITE]);
				close(fd[READ]);
				break ;
			}
			if (ft_strcmp(line, redirect_node->delimiter->word) == 0)
			{
				free(line);
				break ;
			}
			write(fd[WRITE], line, ft_strlen(line));
			write(fd[WRITE], "\n", 1);
			free(line);
		}
		close(fd[WRITE]);
		close(fd[READ]);
		exit(0);
	}
	// 親プロセス
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
	{
		close(fd[READ]);
		close(fd[WRITE]);
		printf("\n");
		return (-2);
	}
	if (WIFSIGNALED(status)) // 子プロセスがシグナルで終了した場合
	{
		close(fd[READ]);
		close(fd[WRITE]);
		printf("\n");
		return (-1);
	}
	close(fd[WRITE]);
	return (fd[READ]);
}
int	handle_redirection(t_node *redirect_node)
{
	if (redirect_node->kind == ND_REDIR_OUT)
		return (open(redirect_node->filename->word,
				O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (redirect_node->kind == ND_REDIR_IN)
		return (open(redirect_node->filename->word, O_RDONLY));
	else if (redirect_node->kind == ND_REDIR_APPEND)
		return (open(redirect_node->filename->word,
				O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (redirect_node->kind == ND_REDIR_HEREDOC)
		return (handle_heredoc(redirect_node));
	else
		perror("Unknown redirection type");
	return (-1);
}

int	open_redir_file(t_node *node)
{
	// printf("node->kind = %d\n", node->kind);
	while (node)
	{
		if (node->kind == ND_PIPELINE)
		{
			if (open_redir_file(node->command) < 0)
				return (-1);
		}
		else if (node->kind == ND_SIMPLE_CMD)
		{
			if (open_redir_file(node->redirects) < 0)
				return (-1);
		}
		else
			node->redirect_fd = handle_redirection(node);
		node = node->next;
	}
	return (0);
}

int	is_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (1);
	else if (node->kind == ND_REDIR_IN)
		return (1);
	else if (node->kind == ND_REDIR_APPEND)
		return (1);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (1);
	return (0);
}

int	redirect(t_node *redirect_node)
{
	if (redirect_node == NULL)
		return (0);
	if (is_redirect(redirect_node))
	{
		if (redirect_node->redirect_fd == -2)
			return (SIGINT_STATUS);
		if (redirect_node->redirect_fd < 0)
			return (1);
		dup2(redirect_node->redirect_fd, redirect_node->default_fd);
		close(redirect_node->redirect_fd);
	}
	else
	{
		perror("failed redirect");
		return (1);
	}
	return (redirect(redirect_node->next));
}

void	close_redirect_fds(t_node *node)
{
	while (node)
	{
		if (node->kind == ND_PIPELINE)
		{
			close_redirect_fds(node->command);
			close_redirect_fds(node->next);
		}
		else if (node->kind == ND_SIMPLE_CMD)
		{
			close_redirect_fds(node->redirects);
		}
		else if (node->redirect_fd > 2)
		{
			close(node->redirect_fd);
			node->redirect_fd = -1;
		}
		node = node->next;
	}
}