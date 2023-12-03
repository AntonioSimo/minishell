/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/26 17:28:50 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int64_t	ft_atoint64_t(const char *str)
{
	int		i;
	int		neg;
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

bool	ft_isnumber(char *str)
{
	int		i;
	bool	check;

	check = false;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		check = true;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (i == 1 && check)
		return (false);
	return (true);
}

void	ft_exit(char **args, t_env *env)
{
	if (ft_arraysize(args) == 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(free_env(env));
	}
	if (!ft_isnumber(args[1]))
	{
		ft_print_message("mustash: exit: ", args[1], \
		": numeric argument required\n", STDERR_FILENO);
		free_env(env);
		exit (2);
	}
	if (ft_arraysize(args) > 2)
	{
		ft_putstr_fd("mustash: exit: too many arguments\n", STDERR_FILENO);
		env->exit_status = ERROR;
	}
	else
	{
		env->exit_status = ft_atoint64_t(args[1]);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit (free_env(env));
	}
}
