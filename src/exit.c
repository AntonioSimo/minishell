#include "../include/minishell.h"

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(char **args)
{
	t_env   env;
	int	exit_code;

	if (args == NULL || args[1] == NULL) 
		exit(0);
	exit_code = ft_atoi(args[1]);
	if (!ft_isnumber(args[1]))
	{
		ft_putstr_fd(RED"exit: numeric argument required\n" RESET, 2);
		//error_code.exit_status = 2;
		env.exit_status = ERROR;
		return (env.exit_status);
	}
	if (ft_arraysize(args) > 2)
	{
		ft_putstr_fd(RED"exit: too many arguments\n"RESET, 2);
		//error_code.exit_status = 1;
		return (1);
	}
	exit(exit_code);
}
