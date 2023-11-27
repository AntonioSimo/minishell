/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:09:40 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:11:09 by pskrucha         ###   ########.fr       */
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

void	ft_cd(t_env *env, t_command *cmd)
{
	char	*nwd;
	char	*up_pwd;

	up_pwd = NULL;
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
	if (chdir(nwd) != 0)
	{
		ft_print_message("mustash: cd: ", nwd, \
		": No such file or directory\n", STDERR_FILENO);
		env->exit_status = ERROR;
	}
	up_pwd = getcwd(up_pwd, PATH_MAXSIZE);
	update_wd(env, "PWD", up_pwd);
	free(nwd);
}
