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

char	*get_cwd(t_env *env)
{
	char	*cwd;
	char	*pwd;

	pwd = NULL;
	cwd = malloc(PATH_MAXSIZE);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAXSIZE))
		return (cwd);
	else
	{
		pwd = get_pwd(env);
		free(cwd);
		return (pwd);
	}
}

char	*get_pwd(t_env *env)
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

void	update_pwd(t_env *env, char *pwd)
{
	t_envepval	*variable;

	variable = env->env;
	while (variable != NULL)
	{
		if (ft_strcmp(variable->key, "OLDPWD") == 0)
		{
			free(variable->val);
			variable->val = ft_strdup(pwd);
			return ;
		}
		variable = variable->next;
	}
}

void	ft_cd(t_env *env, t_command *cmd)
{
	char	*pwd;
	char	*nwd;

	nwd = NULL;
	if (ft_arraysize(cmd->arguments) > 2)
	{
		ft_putstr_fd("mustash: cd: too many arguments\n", STDERR_FILENO);
		env->exit_status = ERROR;
		return ;
	}
	pwd = get_cwd(env);
	if (cmd->arguments[1] == NULL)
	{
		nwd = find_expandable(env->env, "HOME");
		if (chdir(nwd) == -1)
		{
			ft_print_message("mustash: cd: ", nwd, \
			": HOME not set\n", STDERR_FILENO);
			env->exit_status = ERROR;
			free(nwd);
			return ;
		}
		else
		{
			if (nwd)
				free(nwd);
			nwd = find_expandable(env->env, "HOME");
		}
	}
	else if (!ft_strcmp(cmd->arguments[1], "-"))
		nwd = find_expandable(env->env, "OLDPWD");
	else if (cmd->arguments[1])
		nwd = ft_strdup(cmd->arguments[1]);
	if (chdir(nwd) != 0)
	{
		ft_print_message("mustash: cd: ", nwd, \
		": No such file or directory\n", STDERR_FILENO);
		env->exit_status = ERROR;
	}
	else
		if (!nwd)
			chdir(pwd);
	free(pwd);
	free(nwd);
}
