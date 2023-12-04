/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/04 12:52:13 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	env_len(t_envepval *env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

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
	node->next = NULL;
	return (node);
}

void	replace_env_copy(t_env **env)
{
	size_t		size;
	t_envepval	*head;
	int			i;
	char		*key;

	i = 0;
	head = (*env)->env;
	size = env_len((*env)->env);
	(*env)->env_copy = double_free((*env)->env_copy);
	(*env)->env_copy = ptr_check(malloc(sizeof(char *) * (size + 1)));
	while ((*env)->env)
	{
		key = ptr_check(ft_strjoin((*env)->env->key, "="));
		(*env)->env_copy[i] = ptr_check(ft_strjoin(key, (*env)->env->val));
		free(key);
		(*env)->env = (*env)->env->next;
		i++;
	}
	(*env)->env_copy[i] = NULL;
	(*env)->env = head;
}
