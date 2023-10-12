/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:12:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:14:01 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isbuiltin(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

void	exe_builtin(t_command *cmd, t_env *env, int exit_status)
{
	if (ft_strcmp(cmd->command, "cd") == 0)
		ft_cd(env, cmd);
	else if (ft_strcmp(cmd->command, "echo") == 0)
		echo_command(cmd->arguments);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		get_current_working_dir();
	else if (ft_strcmp(cmd->command, "exit") == 0)
		ft_exit(cmd->arguments, env);
	else if (ft_strcmp(cmd->command, "export") == 0)
		ft_export(env, cmd->arguments);
	else if (ft_strcmp(cmd->command, "env") == 0)
		print_my_env(env->env);
	else if (ft_strcmp(cmd->command, "unset") == 0)
		ft_unset(env, cmd->arguments);
	if (exit_status)
		exit (EXIT_SUCCESS);
}
