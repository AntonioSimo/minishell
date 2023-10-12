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

char	*get_cwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAXSIZE);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAXSIZE))
		return (cwd);
	else
	{
		perror("getcwd() error");
		exit (EXIT_FAILURE);
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

static char	*get_home(t_env *env)
{
	char	*nwd;

	nwd = find_expandable(env->env, "HOME");
	if (ft_strlen(nwd) == 0)
	{
		free(nwd);
		nwd = find_home(env->env);
	}
	return (nwd);
}

void	ft_cd(t_env *env, t_command *cmd)
{
	char	*pwd;
	char	*nwd;

	pwd = get_cwd();
	nwd = NULL;
	if (ft_arraysize(cmd->arguments) > 2)
	{
		ft_putstr_fd("mustash: cd: too many arguments\n", STDERR_FILENO);
		env->exit_status = ERROR;
		return ;
	}
	if (cmd->arguments[1] == NULL)
		nwd = get_home(env);
	else if (!ft_strcmp(cmd->arguments[1], "-"))
		nwd = find_expandable(env->env, "OLDPWD");
	else if (cmd->arguments[1])
		nwd = ft_strdup(cmd->arguments[1]);
	if (chdir(nwd) != 0)
	{
		ft_putstr_fd("mustash: cd:", STDERR_FILENO);
		ft_putstr_fd(nwd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		//rintf("mustash: cd: %s: No such file or directory\n", nwd);
		env->exit_status = ERROR;
	}
	else
		update_pwd(env, pwd);
	free(pwd);
	if (nwd)
		free(nwd);
}
