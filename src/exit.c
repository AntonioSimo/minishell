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
		printf("exit\n");
		printf("mustash: exit: %s: numeric argument required\n", args[1]);
		exit (SYNTAX_ERROR);
	}
	if (ft_arraysize(args) > 2)
	{
		printf("exit\n");
		printf("mustash: exit: too many arguments\n");
		env->exit_status = ERROR;
	}
	else
	{
		env->exit_status = ft_atoi(args[1]);
		printf("exit\n");
		exit (env->exit_status);
	}
}
