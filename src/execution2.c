/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 17:30:46 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	run_commands(t_command *cmds, t_env *env)
{
	t_execution	*temp;
	int			check;

	temp = initialize_temp(cmds);
	check = 0;
	if (count_cmds(cmds) == 1 && ft_isbuiltin(cmds->command))
	{
		if (cmds->redirections)
			check = run_redirections(cmds->redirections, env);
		if (!check)
			exe_builtin(cmds, env, 0);
		if (cmds->redirections)
			close_redir(cmds->redirections);
		free_temp(temp);
		return (0);
	}
	handle_multiple_cmds(cmds, env, temp);
	free_temp(temp);
	return (0);
}
