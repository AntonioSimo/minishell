/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:49:20 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:54:50 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    signal_int_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;

	if (sig == SIGINT)
	{
		//g_signal = 128 + SIGINT;
		ft_putstr_fd("\n", STDIN_FILENO);
		//rl_on_new_line();
		g_signal = 1;
	}

	if (info->si_pid != 0)
	{
		if (sig == SIGINT)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
