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

void	ctrl_c_child(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		// printf("here\n");
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	manage_signals(int control)
{
	if (control == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (control == 1)
	{
		signal(SIGINT, ctrl_c_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (control == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (control == 3)
	{
		signal(SIGINT, ctrl_c_child);
		signal(SIGQUIT, SIG_DFL);
	}
}

void    ctrl_c_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
