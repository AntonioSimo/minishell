#include "../include/minishell.h"

int64_t	ft_atoint64_t(const char *str)
{
	int	i;
	int	neg;
	int64_t	result;

	i = 0;
	result = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (neg < 0)
		return (result * neg);
	return (result);
}

bool	ft_isnumber(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+')
		{
			env->exit_status = 100;
			return (false);
		}
		if (str[i] == '-')
		{
			env->exit_status = 156;
			return (false);
		}
		if (!ft_isdigit(str[i]))
		{
			env->exit_status = 255;
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_exit(char **args, t_env *env)
{
	if (ft_arraysize(args) == 1) 
	{
		//printf("exit\n");
		// if (g_signal)
		// 	exit(130);
		exit(env->exit_status);
	}
	if (!ft_isnumber(args[1], env))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_print_message("mustash: exit: ", args[1], ": numeric argument required\n", STDERR_FILENO);
		exit (env->exit_status);
	}
	if (ft_arraysize(args) > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("mustash: cd: too many arguments\n", STDERR_FILENO);
		env->exit_status = ERROR;
	}
	else
	{
		env->exit_status = ft_atoint64_t(args[1]);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit (env->exit_status);
	}
}
