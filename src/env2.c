/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/04 12:33:46 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*copy_env(char **env)
{
	t_envepval	*env_lst;
	size_t		size;
	t_env		*temp;
	int			i;
	char		*key;

	(void) env;
	i = 0;
	env_lst = NULL;
	set_env(&env_lst, env);
	temp = ptr_check(malloc(sizeof(t_env)));
	temp->exit_status = SUCCESS;
	temp->env = env_lst;
	size = env_len(env_lst);
	temp->env_copy = ptr_check(malloc(sizeof(char *) * (size + 1)));
	while (env_lst)
	{
		key = ptr_check(ft_strjoin(env_lst->key, "="));
		temp->env_copy[i] = ptr_check(ft_strjoin(key, env_lst->val));
		free(key);
		env_lst = env_lst->next;
		i++;
	}
	temp->env_copy[i] = NULL;
	return (temp);
}

int	lstenv_c(t_envepval *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (i);
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	*env_str(t_envepval *current)
{
	char	*str;

	str = ft_strdup(current->key);
	if (!str)
		return (NULL);
	str = ft_strjoin(str, "=");
	if (!str)
		return (NULL);
	if (current->val)
		str = ft_strjoin(str, current->val);
	return (str);
}

char	**get_envp(t_env *env)
{
	t_envepval	*current;
	char		**envp;
	int			i;
	char		*temp;

	current = env->env;
	i = 0;
	envp = (char **) malloc(((lstenv_c(current) + 1) * sizeof(char *)));
	if (!envp)
		return (printf("Malloc error"), NULL);
	while (current)
	{
		temp = env_str(current);
		envp[i] = temp;
		current = current->next;
		++i;
	}
	envp[i] = NULL;
	return (envp);
}
