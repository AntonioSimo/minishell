#include "../include/minishell.h"

t_envepval	*lstenv(t_envepval *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void    add_env_variable(t_envepval *lst, t_envepval *new)
{
	t_envepval	*lst_node;

    lst_node = lst;

    // if (lst_node->key = ftrcmp(OK))
    //     previous->next = lst->next;
    //     free current
	if (lst_node == NULL)
	{
		lst_node = new;
		return ;
	}
	lst_node = lstenv(lst);
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

int ft_export(t_env *env, char **args)
{
    t_envepval	*new_variable;
    int i;

    i = 1;
    if (!args[i])
        print_my_env(env->env);
    while (args[i] != NULL)
    {
        if (ft_strchr(args[i], '=') != NULL)
        {
            new_variable = set_newvariable(args[i]);
            if (new_variable != NULL)
            {
               
                add_env_variable((env->env), new_variable);
                //print_my_env(env->env);
            }
                //here update the env with the variable;
        }
    i++;
    }
    return (0);
}    

// int main()
// {
//     char    variabile[50] = "Ciao_Sono_Francesco Ciao_sono_Antonio";
//     char    *variabile_new_env;
//     variabile_new_env = set_newvariable(variabile);
//     printf("%s\n", variabile_new_env);
// }