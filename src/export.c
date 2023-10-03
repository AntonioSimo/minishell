#include "../include/minishell.h"

t_envepval	*lstenv(t_envepval *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_envepval	*create_env_emptynode(char *key, char *value)
{
	t_envepval	*node;

	node = ptr_check(malloc(sizeof(t_export)));
	node->key = ptr_check(ft_strdup(key));
    node->val = ft_strdup(value);
	node->next = NULL;
	return (node);
}

// void	print_my_export(t_export *env)
// {
// 	while (env)
// 	{
// 		ft_printf("%s=%s\n", env->env_variables->key, env->env_variables->val);
//         if (!env->env_variables->val)
//             ft_printf("%s=")
// 		env = env->next;
// 	}
// }

int    ft_isvariable(char *args)
{
	if (!*args || ft_isdigit(*args) || *args == '=' ||
	    (*args == '$' && !*(args + 1)) || *args == ' ')
        {
            printf("im here\n");
		    return (0);
        }
	while (*args && *args != '=')
	{
		if (*args == ' ' || *args == '+')
			return (0);
		args++;
	}
	return (1);
}

void    add_env_variable(t_envepval **lst, t_envepval *new)
{
	t_envepval	*lst_node;

    lst_node = *lst;
	if (lst_node == NULL)
	{
		*lst = new;
		return ;
	}
    while (lst_node->next != NULL)
    {       
        if (ft_strcmp(lst_node->key, new->key) == 0)
        {
            free(lst_node->val);
            lst_node->val = new->val;
            free(new->key);
            free(new);
            return ;
        }
        lst_node = lst_node->next;
    }
    if (ft_strcmp(lst_node->key, new->key) == 0)
    {
        free(lst_node->val);
        lst_node->val = new->val;
        free(new->key);
        free(new);
        return ;
    }
	lst_node->next = new;
}

t_envepval *set_newvariable(char *args)
{
    char          *key;
    char          *val;
    t_envepval    *variable;

    if (!args)
        return (NULL);
    if (!ft_strchr(args, '='))
    {
        key = ft_substr(args, 0, (ft_strlen(args)));
        val = "\0";
    }
    else
    {
        val = ft_strchr(args, '=');
        key = ft_substr(args, 0, (ft_strlen(args) - ft_strlen(val)));
        val++;
    }
    variable = create_env_node(key, val);
    return (variable);
}

void ft_export(t_env *env, char **args)
{
    t_envepval	*new_variable;
    int i;

    i = 1;
    if (!args[i])
        print_my_env(env->env);
    while (args[i] != NULL)
    {
        if (ft_isvariable(args[i]) == 1)
        {
            new_variable = set_newvariable(args[i]);
            if (new_variable != NULL)
                add_env_variable(&(env->env), new_variable);
        }
        else
        {
            perror("mustash: variable not found");
            return ;
        }
    i++;
    }
}    
