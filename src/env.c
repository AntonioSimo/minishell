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
	node->next = NULL;
	return (node);
}

void print_my_env(t_envepval *my_env)
{
    while (my_env)
    {
        if (my_env->val[0])
            printf("%s=%s\n", my_env->key, my_env->val);
        my_env = my_env->next;
    }
}

void	set_env(t_envepval	**my_env, char **env)
{
	int i;
	char *key;
	char *value;
	int equal_pos;
	char    *shlvl;
    t_envepval	*new_variable;

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

t_env  *copy_env(char **env)
{
       t_envepval       *env_lst;
       size_t  size;
	   t_env	*temp;
       int i;
	   (void) env;
       char    *key;

       i = 0;
	   env_lst = NULL;
       set_env(&env_lst, env);
       temp = ptr_check(malloc(sizeof(t_env)));
       temp->exit_status = SUCCESS;
       temp->env = env_lst;
       size = env_len(env_lst);
       temp->env_copy = malloc(sizeof(char *) * (size + 1));
       while(env_lst)
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

 int	lstenv_c(t_envepval *lst)
{
	int i;
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
	char	**envp;
	int		i;
	char	*temp;

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