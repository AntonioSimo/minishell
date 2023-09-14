#include "../include/minishell.h"

/*
It needs to be fixed.
*/

int echo_command(int argc, char **argv)
{
    int     i;
    bool    echo_flag;

    i = 1;
    echo_flag = true;
    if (argc > 1)
    {
        while (argv[i] && ft_strncmp(argv[i], "-n", ft_strlen(argv[2])) == 0)
        {
            echo_flag = false;
            i++;
        }
        while (argv[i])
        {
            ft_putstr_fd(argv[i], 1);
            ft_putchar_fd(' ', 1);
            i++;
        }
    }
    if (echo_flag == true)
        ft_putchar_fd('\n', 1);
    return (0);
}