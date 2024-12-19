/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:37:23 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 05:10:18 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"
# include "struct.h"

int		open_redir_file(t_node *node);
int		is_redirect(t_node *node);
int		redirect(t_node *redirect_node);
void	close_redirect_fds(t_node *node);
int		handle_heredoc(t_node *redirect_node);
#endif