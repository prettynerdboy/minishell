#include "minishell.h"

int handle_redirection(t_node *node) {
    if (node->kind == ND_REDIR_OUT)
        return open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (node->kind == ND_REDIR_IN)
        return open(node->filename->word, O_RDONLY);
    perror("Unknown redirection type");
    return -1;
}

int open_redir_file(t_node *node)
{
    while (node)
    {
        if (node->kind == ND_PIPELINE)
        {
            if (open_redir_file(node->command) < 0 || open_redir_file(node->next) < 0)
                return -1;
        } 
        else if (node->kind == ND_SIMPLE_CMD)
        {
            if (open_redir_file(node->redirects) < 0)
                return -1;
        } 
        else
        {
            node->redirect_fd = handle_redirection(node);
            if (node->redirect_fd < 0)
            {
                perror(node->filename->word);
                return -1;
            }
        }
        node = node->next;
    }
    return 0;
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

void	redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (is_redirect(redir))
	{
		dup2(redir->redirect_fd, redir->default_fd);
        close(redir->redirect_fd);
	}
	else
		perror("faile,redirect");
	redirect(redir->next);
}