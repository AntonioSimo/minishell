/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:01:32 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct s_execution
{
	t_command	*head;
	int			i;
}	t_execution;

t_execution *initialize_temp(t_command *cmds)
{
	t_execution	*temp;

	temp = ptr_check(malloc(sizeof(t_execution)));
	temp->head = cmds;
	temp->i = 0;

	return (temp);
}

void	find_cmd(t_command	*cmd, t_env *env)
{
	char	*path;

	path = find_path(cmd->command, find_expandable(env->env, "PATH"));
	if (path)
		execve(path, cmd->arguments, env->env_copy);
	else
		printf(RED"mustash: %s: command not found\n"RESET, cmd->command);
	exit(127);
}

static int	**make_pipes(t_command *cmds)
{
	int	i;
	int	**fd;

	i = 0;
	if (count_cmds(cmds) > 1)
		fd = ptr_check(malloc(sizeof(int *) * count_cmds(cmds) - 1));
	while (i < count_cmds(cmds) - 1)
	{
		fd[i] = ptr_check(ft_calloc(2, sizeof(int)));
		if (pipe(fd[i]) == -1)
			perror_exit("Pipe error\n");
		i++;
	}
	return (fd);
}

void	handle_child_process(int **fd, t_command *cmds, t_env *env, \
							t_execution	*temp)
{
	int	check;

	check = 0;
	execute_pipe(fd, temp->i, temp->head);
	if (cmds->redirections)
		check = run_redirections(cmds->redirections);
	if (check)
	{
		write(1, "", 1);
		exit(1);
	}
	if (ft_isbuiltin(cmds->command))
		exe_builtin(cmds, env, 1);
	find_cmd(cmds, env);
}

static void	handle_multiple_cmds(t_command *cmds, t_env *env, pid_t *pid, \
								int **fd)
{
	t_execution	*temp;

	temp = initialize_temp(cmds);
	while (cmds)
	{
		pid[temp->i] = fork();
		if (pid[temp->i] == -1)
			return (perror_exit("Fork error\n"));
		if (pid[temp->i] == 0)
			handle_child_process(fd, cmds, env, temp);
		temp->i++;
		cmds = cmds->next;
	}
	cmds = temp->head;
}

int	close_pipes(t_command *cmds, int **fd, pid_t *pid, int *exit_status)
{
	int	i;
	int	status;

	i = 0;
	while (i < count_cmds(cmds))
	{
		if (i < count_cmds(cmds) - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			*exit_status = WEXITSTATUS(status);
			return (*exit_status);
		}
		i++;
	}
	return (SUCCESS);
}

void	run_commands(t_command *cmds, t_env *env)
{
	int			**fd;
	pid_t		*pid;
	int			check;

	check = 0;
	if (count_cmds(cmds) == 1 && ft_isbuiltin(cmds->command))
	{
		if (cmds->redirections)
			check = run_redirections(cmds->redirections);
		if (!check)
			exe_builtin(cmds, env, 0);
		if (cmds->redirections)
			close_redir(cmds->redirections);
		return ;
	}
	pid = ptr_check(malloc(sizeof(pid_t) * count_cmds(cmds)));
	fd = make_pipes(cmds);
	handle_multiple_cmds(cmds, env, pid, fd);
	close_pipes(cmds, fd, pid, &env->exit_status);
}
