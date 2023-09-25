#include "../include/minishell.h"

int ft_isbuiltin(char *command)
{
    if (ft_strncmp(command, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(command, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(command, "env", 3) == 0)
        return (1);
    if (ft_strncmp(command, "exit", 4) == 0)
        return (1);
    return (0);
}

void    exe_builtin(char **args, char *command, t_env *env)
{
    if (ft_strncmp(command, "echo", 4) == 0)
        echo_command(args);
    if (ft_strncmp(command, "pwd", 3) == 0)
        get_current_working_dir();
    if (ft_strncmp(command, "env", 3) == 0)
        print_my_env(env->env);
    if (ft_strncmp(command, "exit", 4) == 0)
        ft_exit(args);
}