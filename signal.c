/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauchida <hauchida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:28:01 by hauchida          #+#    #+#             */
/*   Updated: 2024/12/07 17:54:36 by hauchida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_test(int sig)
{
	return ;
}

int	start_signal(void)
{
	signal(2, signal_handler_test);
	while (1)
		pause();
}