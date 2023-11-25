/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/26 17:39:25 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_pipes(int **fd, t_execution *temp)
{
	if (temp->i == temp->cmds_size - 1)
		close(fd[temp->i - 1][0]);
	else
	{
		close(fd[temp->i][1]);
		if (temp->i != 0)
			close(fd[temp->i - 1][0]);
	}
}

void	get_last_stat(int last_pid, t_command *cmds, t_env *env, int *last_stat)
{
	int	cmds_size;
	int	status;
	int	wait_ret;

	cmds_size = count_cmds(cmds);
	while (cmds_size > 0)
	{
		wait_ret = waitpid(-1, &status, 0);
		if (status == 2)
		{
			printf("\n");
			env->exit_status = 130;
			g_signal = 1;
		}
		else if (status == 131 || status == 3)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			env->exit_status = 131;
			g_signal = 1;
		}
		if (wait_ret == last_pid)
			*last_stat = status;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			cmds_size--;
	}
}

void	wait_last_child(t_command *cmds, int last_pid, t_env *env)
{
	int	last_status;

	last_status = 0;
	get_last_stat(last_pid, cmds, env, &last_status);
	if (WIFEXITED(last_status))
	{
		env->exit_status = WEXITSTATUS(last_status);
		g_signal = 0;
	}
	else
	{
		if (g_signal)
			env->exit_status = 130;
		else
			env->exit_status = SUCCESS;
		g_signal = 0;
	}
}
