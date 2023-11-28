/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 16:21:14 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	**make_pipes(t_command *cmds)
{
	int	i;
	int	**fd;
	int	cmds_size;

	cmds_size = count_cmds(cmds);
	i = 0;
	if (cmds_size == 1)
		return (NULL);
	fd = ptr_check(malloc (sizeof (int *) * (cmds_size - 1)));
	while (i < cmds_size - 1)
	{
		fd[i] = ptr_check(malloc(sizeof(int) * 2));
		i++;
	}
	return (fd);
}

t_execution	*initialize_temp(t_command *cmds)
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
		ft_print_message("mustash: ", cmd->command, ": command not found\n", \
		STDERR_FILENO);
		exit (127);
	}
}

void	is_executable(t_command *cmds, t_env *env)
{
	struct stat	file_info;

	if (access(cmds->command, X_OK) == 0 && stat(cmds->command, \
		&file_info) == 0 && !S_ISDIR(file_info.st_mode))
	{
		execve(cmds->command, cmds->arguments, env->env_copy);
		exit(0);
	}
	if (access(cmds->command, F_OK) != 0)
	{
		ft_print_message("mustash: ", cmds->command, \
		": No such file or directory\n", STDERR_FILENO);
		exit (127);
	}
	if (stat(cmds->command, &file_info) == 0 && S_ISDIR(file_info.st_mode))
		ft_print_message("mustash: ", cmds->command, \
		": Is a directory\n", STDERR_FILENO);
	else
		ft_print_message("mustash: ", cmds->command, \
		": Permission denied\n", STDERR_FILENO);
	exit (126);
}

void	handle_child_process(int **fd, t_command *cmds, t_env *env, \
							t_execution	*temp)
{
	int	check;

	check = 0;
	execute_pipe(fd, temp);
	if (cmds->redirections)
		check = run_redirections(cmds->redirections, env);
	if (ft_strlen(cmds->command) == 0)
		exit(0);
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
