#include "../include/minishell.h"

char    *get_cwd()
{
    char    *cwd;

    cwd = malloc(PATH_MAXSIZE);
    if (!cwd)
        return (NULL);
    if (getcwd(cwd, PATH_MAXSIZE))
        return (cwd);
    else 
    {
        ft_putstr_fd(RED"getcwd() error\n"RESET, 2);
        exit (EXIT_FAILURE);
    }
}

char    *get_pwd(t_env  *env)
{
    t_envepval  *variable;

    variable = env->env;
    while (variable != NULL)
    {
        if (ft_strcmp(variable->key, "OLDPWD") == 0)
            return (variable->val);
        variable = variable->next;
    }
    return (NULL);
}

void    update_pwd(t_env *env, char *pwd)
{
    t_envepval  *variable;

    variable = env->env;
    while (variable != NULL)
    {
        if (ft_strcmp(variable->key, "OLDPWD") == 0)
        {
            free(variable->val);
            variable->val = ft_strdup(pwd);
            return ;
        }
        variable = variable->next;
    }
}

void    ft_cd(t_env *env, char **args)
{
    char    *pwd;
    char    *nwd;


    pwd = get_cwd();
    if (args[1] == NULL)
        nwd = find_expandable(env->env, "HOME"); //I'd switch that to function we have it's called find_expandable, you can find it in expander.c 
    else                       // it's already linked to header file. Why? Because this function calls original env 
        nwd = args[1];          //which is passed to program on the input and we want to be calling our own struct with env
    if (chdir(nwd) != 0)        //cuz you can set HOME to something else later and getenv will look for old value.
                                //in case when HOME is unset we print message 'mustash: cd: HOME not set'
        printf(RED"mustash: cd: %s: No such file or directory\n"RESET, nwd);
    else
        update_pwd(env, pwd);
    free(pwd);
}