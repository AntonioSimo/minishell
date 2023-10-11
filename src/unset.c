#include "../include/minishell.h"

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
	current_node = env->env;
	previous_node = NULL;
	if (!args || !env)
		return ;
	while (current_node != NULL)
	{
		if (ft_strcmp(args[i], current_node->key) == 0)
		{
			if (previous_node == NULL)
				env->env = current_node->next;
			else
				previous_node->next = current_node->next;
			ft_nodedel(current_node);
			return ;
		}
	previous_node = current_node;
	current_node = current_node->next;
	}
}
