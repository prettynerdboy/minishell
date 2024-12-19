/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:36:55 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 05:24:09 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static void	close_fd(int fd[2])
{
	close(fd[READ]);
	close(fd[WRITE]);
}

static int	close_failure(int fd[2], int status, int return_value)
{
	close_fd(fd);
	printf("\n");
	*get_status() = status;
	return (return_value);
}

static pid_t	check_run_heredoc(int fd[2])
{
	pid_t	pid;

	if ((*is_pipe_heredoc() && *is_run_heredoc() && *get_status() == 130)
		|| (!*is_pipe_heredoc()) && *is_run_heredoc())
		return ((pid_t)-2);
	if (pipe(fd) < 0)
	{
		perror("Failed to create pipe");
		return ((pid_t)-1);
	}
	*is_run_heredoc() = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ((pid_t)-1);
	}
	return (pid);
}

static void	run_heredoc_child_proccess(int fd[2], t_node *redirect_node)
{
	char	*line;

	*heredoc_fds() = fd;
	signal(SIGINT, child_signal_handler);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close_fd(fd);
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
	close_fd(fd);
	exit(0);
}

int	handle_heredoc(t_node *redirect_node)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pid = check_run_heredoc(fd);
	if (pid < 0)
		return ((int)pid);
	if (pid == 0) // 子プロセス
		run_heredoc_child_proccess(fd, redirect_node);
	// 親プロセス
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
		return (close_failure(fd, SIGINT_STATUS, -2));
	if (WIFSIGNALED(status)) // 子プロセスがシグナルで終了した場合
		return (close_failure(fd, 1, -1));
	close(fd[WRITE]);
	*get_status() = 0;
	return (fd[READ]);
}
