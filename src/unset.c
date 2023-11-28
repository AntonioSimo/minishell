/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 15:50:06 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal;

void	ft_nodedel(t_envepval *env)
{
	ft_ptrdel(env->key);
	ft_ptrdel(env->val);
	ft_ptrdel(env);
}

static void	delete_node(t_envepval *current_node, t_envepval *previous_node, \
					t_env *env, char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		current_node = env->env;
		previous_node = NULL;
		while (current_node != NULL)
		{
			if (ft_strcmp(args[i], current_node->key) == 0)
			{
				if (previous_node == NULL)
					env->env = current_node->next;
				else
					previous_node->next = current_node->next;
				ft_nodedel(current_node);
				break ;
			}
			previous_node = current_node;
			current_node = current_node->next;
		}
		i++;
	}
}

void	ft_unset(t_env *env, char **args)
{
	t_envepval	*current_node;
	t_envepval	*previous_node;

	current_node = NULL;
	previous_node = NULL;
	if (ft_arraysize(args) < 2 || !env)
	{
		g_signal = 0;
		env->exit_status = SUCCESS;
		return ;
	}
	delete_node(current_node, previous_node, env, args);
	env->exit_status = SUCCESS;
}
