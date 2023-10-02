#include "../include/minishell.h"

t_envepval	*lstenv(t_envepval *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

bool    ft_isvariable(char *args)
{
	if (!*args || ft_isdigit(*args) || *args == '=' || \
	(*args == '$' && !*(args + 1)) || *args == ' ')
		return (false);
	while (*args && *args != '=')
	{
		if (*args == ' ' || *args == '+')
			return (false);
		args++;
	}
	return (true);
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
    val = ft_strchr(args, '=');
    key = ft_substr(args, 0, (ft_strlen(args) - ft_strlen(val)));
    val++;
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
        if (ft_isvariable(args[i]) == true)
        {
            new_variable = set_newvariable(args[i]);
            if (new_variable != NULL)
                add_env_variable(&(env->env), new_variable);
        }
        else
        {
            perror("Export error");
            return ;
        }
    i++;
    }
}    
