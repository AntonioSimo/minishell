#include "../include/minishell.h"

int ft_isbuiltin(char *command)
{
    if (ft_strncmp(command, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(command, "pwd", 3) == 0)
        return (1);
    return (0);
}

int exe_builtin(char **args)
{
    
}