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

void	ft_exit(char **args, t_env *env)
{
	if (args == NULL || args[1] == NULL) 
	{
		printf("exit\n");
		exit(SUCCESS);
	}
	if (!ft_isnumber(args[1]))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_print_message("mustash: exit: ", args[1], ": numeric argument required\n", STDERR_FILENO);
		exit (100);
	}
	if (ft_arraysize(args) > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("mustash: cd: too many arguments\n", STDERR_FILENO);
		env->exit_status = ERROR;
	}
	else
	{
		env->exit_status = ft_atoi(args[1]);
		printf("exit\n");
		exit (env->exit_status);
	}
}
