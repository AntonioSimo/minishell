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

int	lstenv_c(t_envepval *lst)
{
	int i;
	i = 0;
	if (lst == NULL)
		return (i);
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	*env_str(t_envepval *current)
{
	char	*str;

	str = ft_strdup(current->key);
	if (!str)
		return (NULL);
	str = ft_strjoin(str, "=");
	if (!str)
		return (NULL);
	if (current->val)
		str = ft_strjoin(str, current->val);
	return (str);
}

char	**get_envp(t_env *env)
{
	t_envepval	*current;
	char	**envp;
	int		i;
	char	*temp;

	current = env->env;
	i = 0;
	envp = (char **) malloc(((lstenv_c(current) + 1) * sizeof(char *)));
	if (!envp)
		return (printf("Malloc error"), NULL);
	while (current)
	{
		temp = env_str(current);
		envp[i] = temp;
		current = current->next;
		++i;
	}
	envp[i] = NULL;
	return (envp);
}

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
	if (pipe(temp->error_pipe) == -1)
		perror_exit("Pipe creation failed\n");
	return (temp);
}

void	find_cmd(t_command	*cmd, t_env *env, t_execution *temp)
{
	char	*path;
	path = find_path(cmd->command, find_expandable(env->env, "PATH"));
	if (path)
	{	
		if (temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
		close(temp->error_pipe[1]);
		execve(path, cmd->arguments, get_envp(env));
	}
	else
	{
		ft_print_message(NULL, cmd->command, ": command not found\n", 2);
		if (temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
		exit (127);
	}
}


void	is_executable(t_command *cmds, t_env *env, t_execution *temp)
{
	struct stat file_info;
	if (access(cmds->command, X_OK) == 0 && stat(cmds->command, &file_info) == 0 && !S_ISDIR(file_info.st_mode))
	{
		if (temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
		execve(cmds->command, cmds->arguments, get_envp(env));
		exit(0);
	}
	if (access(cmds->command, F_OK) != 0)
	{
		ft_print_message("mustash: ", cmds->command, ": No such file or directory\n", temp->error_pipe[1]);
		if (temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
    	exit (127);
	}
	if (stat(cmds->command, &file_info) == 0 && S_ISDIR(file_info.st_mode))
	{
       	ft_print_message("mustash: ", cmds->command, ": Is a directory\n", 2);
		if (temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
		exit (126);
	}
	else
	{
		ft_print_message("mustash: ", cmds->command, ": Permission denied\n", temp->error_pipe[1]);
		if (temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
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
		check = run_redirections(cmds->redirections, env, temp->error_pipe);
	if (check)
	{
		if (ft_isbuiltin(cmds->command) || temp->i == temp->cmds_size - 1)
			ft_putstr_fd("EOF", temp->error_pipe[1]);
		exit(1);
	}
	if (ft_isbuiltin(cmds->command))
		exe_builtin(cmds, env, 1, temp);
	if (ft_strnstr(cmds->command, "../", ft_strlen(cmds->command))
		|| ft_strnstr(cmds->command, "./", ft_strlen(cmds->command))
		|| ft_strchr(cmds->command, '/'))
		is_executable(cmds, env, temp);
	find_cmd(cmds, env, temp);
}

void	close_pipes(int **fd, t_execution *temp)
{
	if (temp->cmds_size == 1)
	{
		close(temp->error_pipe[1]);
		return ;
	}
	if (temp->i == temp->cmds_size - 1)
	{
		close(fd[temp->i - 1][0]);
		close(temp->error_pipe[1]);
	}
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

//void	print_error(t_execution *var)
//{
//	char 	*line;
//	char	*message;
//	// int	i;

//	// i = 0;

//	if (!line)
//		return;

//	message = ft_strdup("");
//	while (1)
//	{
//		line = get_next_line(var->error_pipe[0]);
//		if (line && !ft_strcmp(line, "EOF"))
//		{
//			if (ft_strlen(message))
//				printf("%s", message);
//			free(message);
//			free(line);
//			break ;
//		}
//		message = ft_free_strjoin(message, line);
//		free(line);
//	}
//	close(var->error_pipe[0]);
//}

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
		close_pipes(temp->fd, temp);
		temp->i++;
		cmds = cmds->next;
	}
	cmds = temp->head;
	wait_last_child(cmds, temp->pid[temp->i - 1], env);
	manage_signals(1);
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
		{
			check = run_redirections(cmds->redirections, env, temp->error_pipe);
		}
		if (!check)
			exe_builtin(cmds, env, 0, temp);
		if (cmds->redirections)
			close_redir(cmds->redirections);
		ft_putstr_fd("EOF", temp->error_pipe[1]);
		close(temp->error_pipe[1]);
		//print_error(temp);
		return ;
	}
	handle_multiple_cmds(cmds, env, temp);
	free_temp(temp);
	// free_pid_fd(pid, fd);
}
