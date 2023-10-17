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
		fd[i] = ptr_check(malloc(sizeof(int) * 2));
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
void	close_pipes(int **fd, t_execution *temp)
{
	int cmds_size;

	cmds_size = count_cmds(temp->head);
	if (cmds_size == 2)
	{
		if (temp->i == 0)
			close(fd[0][1]);
		else
			close(fd[0][0]);
	}
	else
	{
		if (temp->i == 0)
			close(fd[0][1]);
		else if (temp->i % 2)
		{
			if(temp->i == cmds_size - 1)
			{
				close(fd[0][0]);
				close(fd[0][1]);
				close(fd[1][1]);
				close(fd[1][0]);
			}
			else
			{
				close(fd[0][0]);
				close(fd[1][1]);
			}
		}
		else
		{
			
			if(temp->i == cmds_size - 1)
			{
				close(fd[0][0]);
				close(fd[0][1]);
				close(fd[1][1]);
				close(fd[1][0]);
			}
			else
			{
				close(fd[0][1]);
				close(fd[1][0]);
			
			}
			
		}

		
	}
}

static int	handle_multiple_cmds(t_command *cmds, t_env *env, pid_t *pid, \
								int **fd)
{
	t_execution	*temp;

	temp = initialize_temp(cmds);
	while (cmds)
	{
		// printf("i:%i\n", temp->i);
		pid[temp->i] = fork();
		if (pid[temp->i] == -1)
			perror_exit("Fork error\n");
		// signal(SIGINT, SIG_IGN); // here turn off signals or do something with it to be able ctrl c in bash
		// manage_signals(0);
		if (pid[temp->i] == 0)
		{
			manage_signals(2);
			handle_child_process(fd, cmds, env, temp);
		}
		// if (count_cmds(temp->head) > 1)
		// 	close_pipes(fd, temp);
		temp->i++;
		cmds = cmds->next;
	}
	// manage_signals(3);
	cmds = temp->head;
	// printf("pid: %i\n", pid[temp->i - 1]);
	return (pid[temp->i - 1]);
}

static void	wait_last_child(int **fd, t_command *cmds, int last_pid, t_env *env)
{
	int	cmds_size;
	int	wait_ret;
	int status;
	int	i;
	int	last_status;

	i = 0;
	cmds_size = count_cmds(cmds);
	// printf("last pid: %i\ncmds size: %i\n", last_pid, cmds_size);
	if (count_cmds(cmds) == 2)
	{
		close(fd[0][0]);
		close(fd[0][1]);
	}
	else if (count_cmds(cmds) > 2)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[1][0]);
	}
	while (i < cmds_size)
	{
		
		wait_ret = waitpid(-1, &status, 0);
		if (wait_ret == last_pid)
			last_status = status;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			i++;
		
	}
	// printf("here g sig:%i\n", g_signal);
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

// void	free_pid_fd(pid_t *pid, int **fd, t_command *cmds)
// {
// 	int	cmds_size;
// 	int	i;

// 	i = 0;
// 	cmds_size = count_cmds(cmds);
// 	while (i < cmds_size)
	
// 	}
// }
void	run_commands(t_command *cmds, t_env *env)
{
	int			**fd;
	pid_t		*pid;
	int			check;
	int			last_pid;

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
	last_pid = handle_multiple_cmds(cmds, env, pid, fd);
	wait_last_child(fd, cmds, last_pid, env);
	// free_pid_fd(pid, fd);
	
}
