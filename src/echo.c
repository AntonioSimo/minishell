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
    int     j;
    int     x;
    bool    is_nl;
    bool    if_print;
    
    i = 0;
    j = 1;
    x = 1;
    is_nl = true;
    // printf("args size: %i\n", ft_arraysize(args));
    if (ft_arraysize(args) > 1)
    {

        while (args[j])
        {
            if_print = true;
            if (args[j][i] == '-')
            {
                // while(args[j][i] == '-')
                i++;
                if (!args[j])
                    is_nl = true;
                if (args[j][i] && args[j][i] == 'n')
                {
                    while(args[j][i] && args[j][i] == 'n')
                        i++;
                    if (!args[j][i])
                    {
                        is_nl = false;
                        if_print = false;
                    }
                    
                }
                i = 0;

            }
            if (if_print)
            {
                ft_putstr_fd(args[j], 1);
                // printf("j: %i, arr size: %i\n", j, ft_arraysize(args));
                if (j < ft_arraysize(args) - 1)
                    write(1, " ", 1);
            }
            j++;
        }
                // printf("hello\n");
    }
        if (is_nl)
            write(1, "\n", 1);
        // if (args && ft_strcmp(args[i], "-n") == 0)
        // {
        //     i++;
        //     is_nl = true;
        // }
        // else if (args && ft_strncmp(args[i], "-n", 2) == 0)
        // {
        //     i++;
        //     is_nl = true;
        // }
        // if (args[0][0] == '-')
        // {
        //     while (args[i] && ft_strchr(args[i], 'n') == 0)
        //     {
        //         i++;
        //         printf()
        //         is_nl = false;
        //     }
        // }
        // printf("%c\n\n", args[1][2]);
    //     if (args[1][0] == '-')
    //     {
    // 		while (args[1][x] == 'n')
	//     	{
    //             if (args[1][x] != 'n')
    //             {
    //                 is_nl = true;
    //                 break;
    //             }
	// 	    	is_nl = false;
	// 	    	x++;
	// 	    }
    //     }
    //     while (args[i])
    //     {
    //         ft_putstr_fd(args[i], 1);
    //         if (i < ft_arraysize(args) - 1)
    //             ft_putchar_fd(' ', 1);
    //         i++;
    // }
    // if (is_nl == true)
    //     ft_putchar_fd('\n', 1);
}
