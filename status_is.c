#include "minishell.h"


int	**heredoc_fds(void)
{
	static int	*fds;

	return (&fds);
}

int	*is_pipe_heredoc(void)
{
	static int	is_pipe;

	return (&is_pipe);
}

int	*is_run_heredoc(void)
{
	static int	is_run;

	return (&is_run);
}
