/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/23 14:49:59 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_signal;

void	ft_nodedel(t_envepval *env)
{
	if (env && env->next == NULL)
	{
		ft_ptrdel(env->key);
		ft_ptrdel(env->val);
		env->key = NULL;
		env->val = NULL;
		env->next = NULL;
		return ;
	}
	ft_ptrdel(env);
}

void	ft_unset(t_env *env, char **args)
{
	int			i;
	t_envepval	*current_node;
	t_envepval	*previous_node;

	i = 1;
	if (ft_arraysize(args) < 2 || !env)
	{
		g_signal = 0;
		env->exit_status = SUCCESS;
		return ;
	}
	while (args[i] != NULL)
	{
		current_node = env->env;
		previous_node = NULL;
		while (current_node != NULL)
		{
			if (ft_strcmp(args[i], current_node->key) == 0)
			{
				//if (previous_node == NULL)
				//	env->env = current_node->next;
				//else
					previous_node->next = current_node->next;
				ft_nodedel(current_node);
				free(current_node->key);
				free(current_node->val);
				//free(current_node);
				break ;
			}
			previous_node = current_node;
			current_node = current_node->next;
		}
		i++;
	}
}
