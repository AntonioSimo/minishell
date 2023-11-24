/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:57:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_current_working_dir(t_env *env)
{
	char	*current_pwd;
	char	*previous_pwd;

	current_pwd = malloc(PATH_MAXSIZE + 1);
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
	{
		//update_wd(env, "OLDPWD", current_pwd);
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
	free(current_pwd);
	env->exit_status = SUCCESS;
}
