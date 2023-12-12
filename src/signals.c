/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:49:20 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/12 12:46:55 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef enum e_signal_codes {
	CODE1,
	CODE2,
	CODE3,
	CODE4,
}			t_signal_codes;

void	ctrl_c_child(int sig)
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
	else if (control == 4)
	{
		signal(SIGINT, ctrl_c_heredoc);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	ctrl_c_handler(int sig)
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

void	ctrl_c_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
	}
}
