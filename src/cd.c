/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:09:40 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/29 12:19:01 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_old_pwd(t_env *env)
{
	t_envepval	*variable;

	variable = env->env;
	while (variable != NULL)
	{
		if (ft_strcmp(variable->key, "OLDPWD") == 0)
			return (variable->val);
		variable = variable->next;
	}
	return (NULL);
}

char	*get_pwd(t_env *env)
{
	t_envepval	*variable;

	variable = env->env;
	while (variable != NULL)
	{
		if (ft_strcmp(variable->key, "PWD") == 0)
			return (variable->val);
		variable = variable->next;
	}
	return (NULL);
}

static char	*move_home(t_env *env)
{
	char	*nwd;

	nwd = find_expandable(env->env, "HOME");
	if (chdir(nwd) != 0)
	{
		ft_print_message("mustash: cd: ", nwd, \
		": HOME not set\n", STDERR_FILENO);
		env->exit_status = ERROR;
		free(nwd);
		return (NULL);
	}
	free(nwd);
	return (NULL);
}

void	change_dir(char *nwd, t_env *env)
{
	char	*up_pwd;

	up_pwd = NULL;
	if (chdir(nwd) != 0)
	{
		ft_print_message("mustash: cd: ", nwd, \
		": No such file or directory\n", STDERR_FILENO);
		env->exit_status = ERROR;
	}
	up_pwd = getcwd(up_pwd, PATH_MAXSIZE);
	if (up_pwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannotaccess parent directories:", STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	else
		update_wd(env, "PWD", up_pwd);
}

void	ft_cd(t_env *env, t_command *cmd)
{
	char	*nwd;

	nwd = get_cwd(env);
	if (ft_arraysize(cmd->arguments) > 2)
	{
		ft_putstr_fd("mustash: cd: too many arguments\n", STDERR_FILENO);
		env->exit_status = ERROR;
		return ;
	}
	if (cmd->arguments[1] == NULL)
	{
		nwd = move_home(env);
		return ;
	}
	else if (cmd->arguments[1])
		nwd = ft_strdup(cmd->arguments[1]);
	change_dir(nwd, env);
	free(nwd);
}
