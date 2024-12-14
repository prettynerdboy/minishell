#include "minishell.h"

int	set_status(int status)
{
	static int	g_status;

	if (status >= 0)
		g_status = status;
	return (g_status);
}
