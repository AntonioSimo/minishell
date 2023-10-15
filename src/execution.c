/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 16:40:36 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/stat.h>

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
	{
		execve(path, cmd->arguments, env->env_copy);
	}
	else
		ft_print_message(NULL, cmd->command, ": command not found\n", STDERR_FILENO);
	exit (127);
}

static int	**make_pipes(t_command *cmds)
{
	int	i;
	int	**fd;

	i = 0;
	if (count_cmds(cmds) == 1)
		return (NULL);
	if (count_cmds(cmds) == 2)
	{
		fd = ptr_check(malloc(sizeof(int *)));
		i = 1;
	}
	if (count_cmds(cmds) > 2)
	{
		fd = ptr_check(malloc(sizeof(int *) * 2));
		i = 2;
	}
	while (i--)
	{
		fd[i] = ptr_check(ft_calloc(2, sizeof(int)));
		if (pipe(fd[i]) == -1)
			perror_exit("Pipe error\n");
	}
	return (fd);
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
       		ft_print_message("mustash: ", cmds->command, ": Is a directory\n", 2);
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
	execute_pipe(fd, temp->i, temp->head);
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
		// signal(SIGINT, SIG_IGN); // here turn off signals or do something with it to be able ctrl c in bash
		if (pid[temp->i] == 0)
		{
			handle_child_process(fd, cmds, env, temp);
		}
		temp->i++;
		cmds = cmds->next;
	}
	cmds = temp->head;
}

static void	close_pipes(t_command *cmds, int **fd, pid_t *pid, t_env *env)
{
	int		cmds_size;
	int 	status;
	int		i = 0;

	cmds_size = count_cmds(cmds);
	if (cmds_size == 1)
	{
		
		waitpid(pid[0], &status, 0);
		if (WIFEXITED(status))
	    {
			if (g_signal)
				env->exit_status = 130;
			else
				env->exit_status = WEXITSTATUS(status);
			g_signal = 0;
		}
		else
		{
			env->exit_status = SUCCESS;
		}
		return ;
	}
	while (i < cmds_size)
	{
		if (cmds_size == 2)
		{
			close(fd[0][0]);
			close(fd[0][1]);
		}
		else
		{
			close(fd[0][0]);
			close(fd[0][1]);
			close(fd[1][1]);
			close(fd[1][0]);
		}
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
	    {
			g_signal = 0;
			env->exit_status = WEXITSTATUS(status);
		}
		else
		{
			env->exit_status = SUCCESS;
		}
		i++;
	}
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
			check = run_redirections(cmds->redirections, env);
		if (!check)
			exe_builtin(cmds, env, 0);
		if (cmds->redirections)
			close_redir(cmds->redirections);
		return ;
	}
	pid = ptr_check(malloc(sizeof(pid_t) * count_cmds(cmds)));
	fd = make_pipes(cmds);
	handle_multiple_cmds(cmds, env, pid, fd);
	close_pipes(cmds, fd, pid, env);
}
