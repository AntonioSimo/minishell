#include "../include/minishell.h"

int ft_isbuiltin(char *command)
{
    if (ft_strcmp(command, "cd") == 0)
        return (1);
    if (ft_strcmp(command, "echo") == 0)
        return (1);
    if (ft_strcmp(command, "pwd") == 0)
        return (1);
    if (ft_strcmp(command, "exit") == 0)
        return (1);
    if (ft_strcmp(command, "export") == 0)
        return (1);
    if (ft_strcmp(command, "env") == 0)
        return (1);
    if (ft_strcmp(command, "unset") == 0)
        return (1);
    return (0);
}

void    exe_builtin(char **args, char *command, t_env *env)
{
    if (ft_strcmp(command, "cd") == 0)
        ft_cd(env, args);
    if (ft_strcmp(command, "echo") == 0)
        echo_command(args);
    if (ft_strcmp(command, "pwd") == 0)
        get_current_working_dir();
    if (ft_strcmp(command, "exit") == 0)
        ft_exit(args);
    if (ft_strcmp(command, "export") == 0)
        ft_export(env, args);
    if (ft_strcmp(command, "env") == 0)
        print_my_env(env->env);
    if (ft_strcmp(command, "unset") == 0)
        ft_unset(env, args);
}