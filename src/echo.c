#include "../include/minishell.h"

/*
It needs to be fixed.
*/

int echo_command(int argc, char **argv)
{
    int     i;
    bool    is_nl;
    
    argv++;

    i = 1;
    is_nl = false;
    if (argc > 1)
    {
        if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
        {
            i++;
            is_nl = true;
        }
        while (argv[i])
        {
            ft_putstr_fd(argv[i], 1);
            ft_putchar_fd(' ', 1);
            i++;
        }
    }
    if (is_nl == false)
        ft_putchar_fd('\n', 1);
    return (0);
}