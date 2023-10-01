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
    if (args[1] == NULL)
        nwd = getenv("HOME");
    else
        nwd = args[1];
    if (chdir(nwd) != 0)
        perror("chdir() error");
    else
        update_pwd(env, pwd);
    free(pwd);
}