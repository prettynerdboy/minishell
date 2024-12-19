/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:36:26 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 05:27:34 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

static int	handle_redirection(t_node *redirect_node)
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
