/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:15:54 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 13:46:54 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_arraysize(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	check_nl(char **args, bool *is_nl, int j, bool *if_print)
{
	int	i;

	i = 0;
	i++;
	if (!args[j])
		*is_nl = true;
	if (args[j][i] && args[j][i] == 'n')
	{
		while (args[j][i] && args[j][i] == 'n')
			i++;
		if (!args[j][i])
		{
			*is_nl = false;
			*if_print = false;
		}
	}
}

void	echo_token(bool *valid, char **args, int j)
{
	*valid = false;
	ft_putstr_fd(args[j], 1);
	if (j < ft_arraysize(args) - 1)
		write(1, " ", 1);
}

void	echo_command(char **args, t_env *env)
{
	int		j;
	bool	is_nl;
	bool	if_print;
	bool	valid;

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
				echo_token(&valid, args, j);
			j++;
		}
	}
	if (is_nl)
		write(1, "\n", 1);
	env->exit_status = SUCCESS;
	g_signal = 0;
}
