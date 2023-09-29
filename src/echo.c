#include "../include/minishell.h"

int ft_arraysize(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

void echo_command(char **args)
{
    int     i;
    bool    is_nl;
    
    i = 1;
    is_nl = false;
    if (ft_arraysize(args) > 1)
    {
        if (args && ft_strcmp(args[i], "-n") == 0)
        {
            i++;
            is_nl = true;
        }
        else if (args && ft_strncmp(args[i], "-n", 2) == 0)
        {
            i++;
            is_nl = true;
        }
        while (args[i])
        {
            ft_putstr_fd(args[i], 1);
            if (i < ft_arraysize(args) - 1)
                ft_putchar_fd(' ', 1);
            i++;
        }
    }
    if (is_nl == false)
        ft_putchar_fd('\n', 1);
}