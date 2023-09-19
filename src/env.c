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

size_t env_len(t_envepval *env)
{
    size_t i;
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

t_env  *copy_env(t_envepval *env)
{
       t_env   *new_env;
       size_t  size;
       int i;
       char    *key;

       i = 0;
       new_env = ptr_check(malloc(sizeof(t_env)));
       new_env->env = env;
       size = env_len(env);
       new_env->env_copy = malloc(sizeof(char *) * (size + 1));
       while(env)
       {
               key = ft_strjoin(env->key, "=");
               new_env->env_copy[i] = ft_strjoin(key, env->val);
               free(key);
               env = env->next;
               i++;
       }
       printf("hello\n");
       new_env->env_copy[i] = NULL;
       return (new_env);
 }

void	set_env(t_envepval	**my_env, char **env)
{
	int i;
	char *key;
	char *value;
	int equal_pos;
	char    *shlvl;

	i = 0;
	while (env[i])
	{
		equal_pos = find_equal(env[i]);
		key = ptr_check(ft_substr(env[i], 0, equal_pos));
		value = ptr_check(ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]) - equal_pos));
		if (!ft_strncmp(key, "SHLVL", 5))
        {
            	shlvl = ft_itoa(ft_atoi(value) + 1);
            	free(value);
                value = ft_strdup(shlvl);
                free(shlvl);
        }
		envlst_add(my_env, create_env_node(key, value));
		ft_free(key);
		ft_free(value);
		i++;
	}
}

void   print_copy_env(t_env *env)
{
       printf("my struct: \n");
       print_my_env(env->env);
       printf("after----\n");
       printf("my copy:\n\n");
       int i = 0;
       while (env->env_copy[i])
       {
               printf("%s\n", env->env_copy[i]);
               i++;
       }
}