/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 18:02:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envepval	*lstenv(t_envepval *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	envlst_add(t_envepval **lst, t_envepval *new)
{
	t_envepval	*lst_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_node = lstenv(*lst);
	lst_node->next = new;
}

t_envepval	*create_env_node(char *key, char *value)
{
	t_envepval	*node;

	node = ptr_check(malloc(sizeof(t_envepval)));
	node->key = ptr_check(ft_strdup(key));
	node->val = ptr_check(ft_strdup(value));
	if (node->val == NULL)
	{
		node->val = malloc(1);
		node->val[0] = '\0';
	}
	node->next = NULL;
	return (node);
}

void	print_my_env(t_envepval *my_env)
{
	while (my_env)
	{
		if (my_env->val != NULL)
			printf("%s=%s\n", my_env->key, my_env->val);
		my_env = my_env->next;
	}
}

void	set_env(t_envepval	**my_env, char **env)
{
	int			i;
	char		*key;
	char		*value;
	int			equal_pos;
	char		*shlvl;
	t_envepval	*new_variable;

	i = 0;
	while (env[i])
	{
		equal_pos = find_equal(env[i]);
		key = ptr_check(ft_substr(env[i], 0, equal_pos));
		value = ptr_check(ft_substr(env[i], equal_pos + 1, \
				ft_strlen(env[i]) - equal_pos));
		if (!ft_strncmp(key, "SHLVL", 5))
		{
			shlvl = ft_itoa(ft_atoi(value) + 1);
			free(value);
			value = ft_strdup(shlvl);
			free(shlvl);
		}
		else
		{
			new_variable = set_newvariable("SHLVL=1");
			if (new_variable != NULL)
				add_env_variable(my_env, new_variable);
		}
		envlst_add(my_env, create_env_node(key, value));
		ft_free(key);
		ft_free(value);
		i++;
	}
}
