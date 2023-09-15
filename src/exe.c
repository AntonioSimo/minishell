#include "../include/minishell.h"

int ft_isbuiltin(char *command)
{
    if (ft_strncmp(command, "echo", 4) == 0)
        return (1);
    if (ft_strncmp(command, "pwd", 3) == 0)
        return (1);
    return (0);
}

void    exe_builtin(int argc, char **args)
{
    if (ft_strncmp(args[0], "echo", 4) == 0)
        echo_command(argc, args);
    if (ft_strncmp(args[0], "pwd", 3) == 0)
        get_current_working_dir();
}