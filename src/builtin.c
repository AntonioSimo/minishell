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

void	exe_builtin(char **args, char *command, t_env *env, int if_exit)
{
	if (ft_strcmp(command, "cd") == 0)
		ft_cd(env, args);
	else if (ft_strcmp(command, "echo") == 0)
		echo_command(args);
	else if (ft_strcmp(command, "pwd") == 0)
		get_current_working_dir();
	else if (ft_strcmp(command, "exit") == 0)
		ft_exit(args);
	else if (ft_strcmp(command, "export") == 0)
		ft_export(env, args);
	else if (ft_strcmp(command, "env") == 0)
		print_my_env(env->env);
	else if (ft_strcmp(command, "unset") == 0)
		ft_unset(env, args);
	if (if_exit)
		exit(EXIT_SUCCESS);
}
