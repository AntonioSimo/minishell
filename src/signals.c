/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:49:20 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/21 16:25:34 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signal;

void    signal_int_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_quit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		return ;
	}
}