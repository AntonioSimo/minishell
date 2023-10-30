/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:39:33 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:41:03 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_expandable(t_envepval	*env, char	*key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key))
			&& !ft_strncmp(key, env->key, ft_strlen(key)))
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (ft_strdup(""));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*make_str_from_2d(char **args)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (args)
	{
		while (args[i])
		{
			str = ft_free_strjoin(str, args[i]);
			if (args[i + 1])
				str = ft_free_strjoin(str, " ");
			i++;
		}
	}
	return (str);
}

int	is_word(t_type type)
{
	if (type == DEFAULT || type == SINGLE_QUOTED
		|| type == DOUBLE_QUOTED)
		return (1);
	return (0);
}

int	count_cmds(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}
