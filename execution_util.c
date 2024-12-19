#include "minishell.h"

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