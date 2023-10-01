#include "../include/minishell.h"

int ft_arraysize(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void    check_nl(char **args, bool *is_nl, int j, bool *if_print)
{
	int i;

	i = 0;
	i++;
	if (!args[j])
		*is_nl = true;
	if (args[j][i] && args[j][i] == 'n')
	{
		while(args[j][i] && args[j][i] == 'n')
			i++;
		if (!args[j][i])
		{
			*is_nl = false;
			*if_print = false;
		}			
	}
}

void echo_command(char **args)
{
	int     j;
	bool    is_nl;
	bool    if_print;
	bool    valid; // this is to check if we need to validate -n, it will be set into not valid when we start printing text
					//so it means when we will start printing text and will encounter -n, we will not be checking it is a flag
					// e.g. echo -n o -n needs to print o -n
	j = 1;
	valid = true;
	is_nl = true;
	if (ft_arraysize(args) > 1)
	{
		while (args[j])
		{
			if_print = true;
			if (valid && args[j][0] == '-')
			   check_nl(args, &is_nl, j, &if_print);
			if (if_print)
			{
				valid = false;
				ft_putstr_fd(args[j], 1);
				if (j < ft_arraysize(args) - 1)
					write(1, " ", 1);
			}
			j++;
		}
	}
	if (is_nl)
		write(1, "\n", 1);
}
