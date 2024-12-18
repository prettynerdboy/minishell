/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:28:01 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/18 09:55:26 by hauchida         ###   ########.fr       */
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