/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 18:02:04 by pskrucha         ###   ########.fr       */
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

static void	wait_last_child(t_command *cmds, int last_pid, t_env *env)
{
	int	cmds_size;
	int	wait_ret;
	int	status;
	int	last_status;

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
			last_status = status;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			cmds_size--;
	}
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

static void	handle_multiple_cmds(t_command *cmds, t_env *env, t_execution *temp)
{
	while (cmds)
	{
		if (temp->cmds_size > 1 && temp->i < temp->cmds_size - 1)
		{
			if (pipe(temp->fd[temp->i]) == -1)
				perror_exit("Pipe creation failed\n");
		}
		temp->pid[temp->i] = fork();
		if (temp->pid[temp->i] == -1)
			perror_exit("Fork error\n");
		manage_signals(0);
		if (temp->pid[temp->i] == 0)
		{
			manage_signals(3);
			handle_child_process(temp->fd, cmds, env, temp);
		}
		if (temp->cmds_size > 1)
			close_pipes(temp->fd, temp);
		temp->i++;
		cmds = cmds->next;
	}
	cmds = temp->head;
	wait_last_child(cmds, temp->pid[temp->i - 1], env);
	manage_signals(1);
}

void	free_temp(t_execution *temp)
{
	int	i;

	i = 0;
	if (temp->cmds_size > 1)
	{
		while (i < temp->cmds_size - 1)
		{
			free(temp->fd[i]);
			i++;
		}
		free(temp->fd);
		i = 0;
	}
	free(temp->pid);
	i++;
	temp->head = NULL;
	free(temp);
	temp = NULL;
}

void	run_commands(t_command *cmds, t_env *env)
{
	t_execution	*temp;
	int			check;

	temp = initialize_temp(cmds);
	check = 0;
	if (init_heredoc(temp))
	{
		return ;
	}
	if (count_cmds(cmds) == 1 && ft_isbuiltin(cmds->command))
	{
		if (cmds->redirections)
			check = run_redirections(cmds->redirections, env);
		if (!check)
			exe_builtin(cmds, env, 0);
		if (cmds->redirections)
			close_redir(cmds->redirections);
		free_temp(temp);
		return ;
	}
	handle_multiple_cmds(cmds, env, temp);
	free_temp(temp);
}
