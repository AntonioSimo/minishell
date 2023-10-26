/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/26 17:30:08 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/stat.h>

static int	**make_pipes(t_command *cmds)
{
	int	i;
	int	**fd;
	int	cmds_size;

	cmds_size = count_cmds(cmds);	
	i = 0;
	if (cmds_size == 1)
		return (NULL);
	fd = ptr_check(malloc(sizeof(int*) * (cmds_size - 1)));
	while (i < cmds_size - 1)
	{
		fd[i] = ptr_check(malloc(sizeof(int) * 2));
		i++;
	}
	return (fd);
}

t_execution *initialize_temp(t_command *cmds)
{
	t_execution	*temp;

	temp = ptr_check(malloc(sizeof(t_execution)));
	temp->head = cmds;
	temp->i = 0;
	temp->cmds_size = count_cmds(cmds);
	temp->pid = ptr_check(malloc(sizeof(pid_t) * temp->cmds_size));
	temp->fd = make_pipes(cmds);
	return (temp);
}

void	find_cmd(t_command	*cmd, t_env *env)
{
	char	*path;
	path = find_path(cmd->command, find_expandable(env->env, "PATH"));
	if (path)
		execve(path, cmd->arguments, env->env_copy);
	else
	{
		ft_print_message(NULL, cmd->command, ": command not found\n", STDERR_FILENO);
		exit (127);
	}
}


void	is_executable(t_command *cmds, t_env *env)
{
	struct stat file_info;
	if (access(cmds->command, X_OK) == 0 && stat(cmds->command, &file_info) == 0 && !S_ISDIR(file_info.st_mode))
	{
		execve(cmds->command, cmds->arguments, env->env_copy);
		exit(0);
	}
	if (access(cmds->command, F_OK) != 0)
	{
		ft_print_message("mustash: ", cmds->command, ": No such file or directory\n", STDERR_FILENO);
    	exit (127);
	}
	if (stat(cmds->command, &file_info) == 0 && S_ISDIR(file_info.st_mode))
	{
       	ft_print_message("mustash: ", cmds->command, ": Is a directory\n", STDERR_FILENO);
		exit (126);
	}
	else
	{
		ft_print_message("mustash: ", cmds->command, ": Permission denied\n", STDERR_FILENO);
    	exit (126);
	}
}
void	handle_child_process(int **fd, t_command *cmds, t_env *env, \
											 t_execution	*temp)
{
	int	check;

	check = 0;
	execute_pipe(fd, temp);
	if (cmds->redirections)
		check = run_redirections(cmds->redirections, env);
	if (check)
		exit(1);
	if (ft_isbuiltin(cmds->command))
		exe_builtin(cmds, env, 1);
	if (ft_strnstr(cmds->command, "../", ft_strlen(cmds->command))
		|| ft_strnstr(cmds->command, "./", ft_strlen(cmds->command))
		|| ft_strchr(cmds->command, '/'))
		is_executable(cmds, env);
	find_cmd(cmds, env);
}
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
	int status;
	int	last_status;

	cmds_size = count_cmds(cmds);
	while (cmds_size > 0)
	{
		wait_ret = waitpid(-1, &status, 0);
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
		// manage_signals(0);
		if (temp->pid[temp->i] == 0)
		{
			// manage_signals(2);
			handle_child_process(temp->fd, cmds, env, temp);
		}
		// manage_signals(3);
		if (temp->cmds_size > 1)
			close_pipes(temp->fd, temp);
		temp->i++;
		cmds = cmds->next;
	}
	// manage_signals(3);
	cmds = temp->head;
	wait_last_child(cmds, temp->pid[temp->i - 1], env);
}

void	free_temp(t_execution *temp)
{
	int	i;

	i = 0;
	while (i < temp->cmds_size - 1)
	{
		free(temp->fd[i]);
		i++;
	}
	free(temp->fd);
	free(temp->pid);
	temp->head = NULL;
	free(temp);
}

void	run_commands(t_command *cmds, t_env *env)
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
		return ;
	}
	handle_multiple_cmds(cmds, env, temp);
	free_temp(temp);
}
