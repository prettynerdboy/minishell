/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soaoki <soaoki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:28:01 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/20 01:44:01 by soaoki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_prompt(void)
{
	int	*status;
	int	heredoc_fd;

	status = get_status();
	printf("\n");
	rl_on_new_line();       // 新しい行を作成
	rl_replace_line("", 0); // 現在の入力行をクリア
	rl_redisplay();         // プロンプトを再表示
	*status = SIGINT_STATUS;
}

void child_signal_handler(int sig)
{
	int *fds;

	fds = *heredoc_fds();
	if (sig == SIGINT)
	{
		if (fds[0] > 2)
			close(fds[0]);
		if (fds[1] > 2)
			close(fds[1]);
		exit(130);
	}
}

void	signal_handler(int sig)
{
	int status;
	t_data *data;

	data = get_data();
	// printf("signal_handler: %d\n", sig);
	if (sig == SIGINT)
	{
		status = *get_status();
		reset_prompt();
		if (status == 1)
			return ;
		free_data(&data);
	}
}