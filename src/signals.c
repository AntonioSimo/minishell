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

void	ft_signal(t_env *main)
{
	signal(SIGINT, signal_int_handler);
	main->exit_status = g_signal;
	printf("ft_signal->main.exit_status:%i\n", main->exit_status);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_int_handler(int sig)
{

	if (sig == SIGINT)
	{
		g_signal = 128 + SIGINT;
		printf("signal_handler->g_signal:%i\n", g_signal);
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
