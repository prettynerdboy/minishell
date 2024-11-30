#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		free(line);
	}
	exit(0);
}