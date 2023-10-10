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

t_env	exit_s;

void	signal_int_handler(int sig)
{

	if (sig == SIGINT)
	{
		exit_s.exit_status= TERMINATION_SIGINT;
		printf("exit status: %d\n", exit_s.exit_status);
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
