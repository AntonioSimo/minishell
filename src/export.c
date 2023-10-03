#include "../include/minishell.h"

t_export	*create_export_node(char *key, char *value)
{
	t_export	*node;

	node = ptr_check(malloc(sizeof(t_export)));
	node->key = ptr_check(ft_strdup(key));
	node->val = ptr_check(ft_strdup(value));
	node->next = NULL;
	return (node);
}

t_export	*lstenv(t_export *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int    ft_isvariable(char *args)
{
	if (!*args || ft_isdigit(*args) || *args == '=' || \
	(*args == '$' && !*(args + 1)) || *args == ' ')
		return (0);
	while (*args && *args != '=')
	{
		if (*args == ' ' || *args == '+')
			return (0);
		args++;
	}
	return (1);
}

void    add_env_variable(t_export **lst, t_export *new)
{
	t_export	*lst_node;

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

t_export *set_newvariable(char *args)
{
    char          *key;
    char          *val;
    t_export    *variable;

    if (!args)
        return (NULL);
    val = ft_strchr(args, '=');
    key = ft_substr(args, 0, (ft_strlen(args) - ft_strlen(val)));
    val++;
    printf("This is the value:%s\n", val);
    printf("This is the key:%s\n", key);
    variable = create_env_node(key, val);
    return (variable);
}

void ft_export(t_env *env, char **args)
{
    t_export	*new_variable;
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
            perror("Export error");
            return ;
        }
    i++;
    }
}    
