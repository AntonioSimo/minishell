/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 16:38:58 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_wd(t_env *env, char *wd, char *new_wd_value)
{
	t_envepval	*variable;

	variable = env->env;
	while (variable != NULL)
	{
		if (ft_strcmp(variable->key, wd) == 0)
		{
			free(variable->val);
			variable->val = ft_strdup(new_wd_value);
			break ;
		}
		variable = variable->next;
	}
	free(new_wd_value);
}

char	*get_cwd(t_env *env)
{
	char	*cwd;
	char	*pwd;

	pwd = NULL;
	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAXSIZE);
	if (cwd)
	{
		update_wd (env, "OLDPWD", cwd);
		return (cwd);
	}
	else
	{
		pwd = get_old_pwd(env);
		free(cwd);
		return (pwd);
	}
}

void	previous_pwd(t_env *env)
{
	char	*previous_pwd;

	previous_pwd = get_pwd(env);
	if (previous_pwd != NULL)
	{
		ft_putstr_fd(previous_pwd, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		perror("getcwd");
		env->exit_status = ERROR;
	}
}

void	get_current_working_dir(t_env *env)
{
	char	*current_pwd;

	current_pwd = malloc(PATH_MAXSIZE);
	if (!current_pwd)
	{
		env->exit_status = ERROR;
		return ;
	}
	if (getcwd(current_pwd, PATH_MAXSIZE) != NULL)
	{
		ft_putstr_fd(current_pwd, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		previous_pwd(env);
	free(current_pwd);
	env->exit_status = SUCCESS;
}
