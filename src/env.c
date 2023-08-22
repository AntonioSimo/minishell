#include "../include/minishell.h"

static t_envepval	*lstenv(t_envepval *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	envlst_add(t_envepval **lst, t_envepval *new)
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

void	print_my_env(t_envepval *my_env)
{
	while (my_env)
	{
		ft_printf("%s=%s\n", my_env->key, my_env->val);
		my_env = my_env->next;
	}
}

void	set_env(t_envepval	**my_env, char **env)
{
	int i;
	char *key;
	char *value;
	int equal_pos;

	i = 0;
	while (env[i])
	{
		equal_pos = find_equal(env[i]);
		key = ft_substr(env[i], 0, equal_pos);
		value = ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]) - equal_pos);
		envlst_add(my_env, ptr_check(create_env_node(key, value)));
		ft_free(key);
		ft_free(value);
		i++;
	}
}