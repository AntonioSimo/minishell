#include "../include/minishell.h"

bool    ft_isnumber(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]))
            return (false);
        i++;
    }
    return (true);
}

int ft_exit(int argc, char **argv)
{
    int exit_code;

    exit_code = ft_atoi(argv[1]);
    if (argc > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        return (1);
    }
    if (!ft_isnumber(argv[1]))
    {
        ft_putstr_fd("exit: numeric argument required\n", 2);
        return (1);
    }
    exit(exit_code);
}