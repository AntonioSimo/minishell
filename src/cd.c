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
        perror("getcwd() error");
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
    nwd = NULL;
    if (args[1] == NULL)
    {
        nwd = find_expandable(env->env, "HOME");
        if (ft_strlen(nwd) == 0)
        {
            free(nwd);
            nwd = find_home(env->env);
        }
    }
    else if(!ft_strcmp(args[1], "-"))
        nwd = find_expandable(env->env, "OLDPWD");
    else if(args[1])
        nwd = ft_strdup(args[1]);
    if (chdir(nwd) != 0)
        perror("chdir() error");
    else
        update_pwd(env, pwd);
    free(pwd);
    if (nwd)
        free(nwd);
}