/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/12 12:16:39 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_env(t_env *env)
{
	t_envepval	*temp;
	int			exit_code;

	exit_code = env->exit_status;
	double_free(env->env_copy);
	while (env->env)
	{
		temp = env->env->next;
		if (env->env->key)
			free(env->env->key);
		if (env->env->val)
			free(env->env->val);
		free(env->env);
		env->env = temp;
	}
	free(env);
	return (exit_code);
}

static void	second_part(char **args, char **new_args, char *str)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			new_args[i] = ptr_check(ft_strdup(args[i]));
			i++;
		}
	}
	if (str)
	{
		new_args[i] = ptr_check(ft_strdup(str));
		new_args[i + 1] = NULL;
	}
	else
		new_args[i] = NULL;
	if (args)
		args = double_free(args);
}

char	**push_str_2d(char **args, char *str)
{
	int		i;
	char	**new_args;

	i = 0;
	if (!str)
		return (args);
	if (!args && !str)
		return (NULL);
	if (args)
	{
		while (args[i])
			i++;
	}
	if (str)
		new_args = ptr_check(malloc(sizeof(char *) * (i + 2)));
	else
		new_args = ptr_check(malloc(sizeof(char *) * (i + 1)));
	second_part(args, new_args, str);
	return (new_args);
}

void	*ft_ptrdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

int	strlen_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}
