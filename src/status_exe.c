/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/12 16:56:08 by asimone          ###   ########.fr       */
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

	(void)env;
	cmds_size = count_cmds(cmds);
	while (cmds_size > 0)
	{
		wait_ret = waitpid(-1, &status, 0);
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
		env->exit_status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
	{
		env->exit_status = 128 + WTERMSIG(last_status);
		if (WTERMSIG(last_status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else if (WTERMSIG(last_status) == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
	}
}
