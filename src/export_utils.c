/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/27 16:33:50 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envepval	*create_env_emptynode(char *key)
{
	t_envepval	*node;
	//char		empty[1];

	node = ptr_check(malloc(sizeof(t_envepval)));
	node->key = ptr_check(ft_strdup(key));
	//node->val = malloc(1);
	node->val = NULL;
	node->next = NULL;
	return (node);
}

void	print_my_export(t_envepval *env)
{
	while (env)
	{
		if (env->key && !env->val)
			printf("declare -x %s\n", env->key);
		else if (env->val && env->val[0] != '\0')
			printf("declare -x %s='%s'\n", env->key, env->val);
		else if (env->val && env->val[0] == 0)
			printf("declare -x %s=''\n", env->key);
		env = env->next;
	}
}

int	ft_isvariable(char *args)
{
	if (*args == '=')
		return (0);
	while (*args && *args != '=')
	{	
		if (!*args || ft_isdigit(*args) || *args == '=' || \
		(*args == '$' && !*(args + 1)) || *args == ' ')
		{
			return (0);
		}
		if (*args == ' ' || *args == '+' || *args == '-')
		{
			return (0);
		}
		args++;
	}
	return (1);
}
// export a b c