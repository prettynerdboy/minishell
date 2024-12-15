#include "minishell.h"


int handle_heredoc(t_node *redirect_node)
{
    int fd[2];
    char *line;
    if (pipe(fd) < 0)
    {
        perror("Failed to create pipe");
        return -1;
    }
    while (1)
    {
        line = readline("> ");
        if (!line) 
            break;
        if (ft_strcmp(line, redirect_node->delimiter->word) == 0)
        {
            free(line);
            break;
        }
        write(fd[WRITE], line, ft_strlen(line));
        write(fd[WRITE], "\n", 1); 
        free(line);
    }
    close(fd[WRITE]);
    return fd[READ];
}
int handle_redirection(t_node *redirect_node)
{
    if (redirect_node->kind == ND_REDIR_OUT)
        return open(redirect_node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (redirect_node->kind == ND_REDIR_IN)
        return open(redirect_node->filename->word, O_RDONLY);
    else if (redirect_node->kind == ND_REDIR_APPEND)
        return open(redirect_node->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else if (redirect_node->kind == ND_REDIR_HEREDOC)
		return handle_heredoc(redirect_node);
    else
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

int redirect(t_node *redirect_node)
{
    if (redirect_node == NULL)
        return (0);
    if (is_redirect(redirect_node))
    {
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