#include "minishell.h"

void	init_pipe(t_node *node)
{
	if (pipe(node->outpipe) < 0)
		perror("pipe");
	node->next->inpipe[READ] = node->outpipe[READ];
	node->next->inpipe[WRITE] = node->outpipe[WRITE];
}

void	connect_pipe(t_node *node)
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