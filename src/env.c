/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/27 15:56:42 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	check_path(t_env *my_env)
{
	t_envepval	*variable;
	bool		found;

	found = false;
	variable = my_env->env;
	while (variable != NULL)
	{
		if (ft_strcmp(variable->key, "PATH") == 0)
		{
			found = true;
			return (found);
		}
		variable = variable->next;
	}
	ft_print_message("mustash: ", "env: ", "No such file or directory\n", \
					STDERR_FILENO);
	my_env->exit_status = 127;
	return (found);
}

void	print_my_env(t_env *my_env)
{
	t_envepval	*variable;

	variable = my_env->env;
	if (check_path(my_env) == true)
	{
		while (variable)
		{
			if (variable->val)
			{
				printf("%s=%s\n", variable->key, variable->val);
			}
			variable = variable->next;
		}
	}
}

char	*handle_shlvl(char *value)
{
	char		*shlvl;
	char		*ret;

	shlvl = ft_itoa(ft_atoi(value) + 1);
	ret = ft_strdup(shlvl);
	free(shlvl);
	free(value);
	return (ret);
}

void	set_env(t_envepval	**my_env, char **env)
{
	int			i;
	char		*key;
	char		*value;
	int			equal_pos;

	i = 0;
	while (env[i])
	{
		equal_pos = find_equal(env[i]);
		key = ptr_check(ft_substr(env[i], 0, equal_pos));
		value = ptr_check(ft_substr(env[i], equal_pos + 1, \
				ft_strlen(env[i]) - equal_pos));
		if (!ft_strncmp(key, "SHLVL", 5))
			value = handle_shlvl(value);
		envlst_add(my_env, create_env_node(key, value));
		ft_free(key);
		ft_free(value);
		i++;
	}
}
