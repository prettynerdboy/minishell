#include "minishell.h"

int	is_blank(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_meta(char c)
{
	if (is_blank(c) || (c && ft_strchr("|<>&%(){}[];:*~#@\n", c)))
		return (1);
	else
		return (0);
}

int	is_word(char c)
{
	if (c && !is_meta(c))
		return (1);
	else
		return (0);
}