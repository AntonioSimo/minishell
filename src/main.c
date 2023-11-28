/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 17:42:50 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

void	minishell(t_env *my_env)
{
	char	*line;

	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
		{
			if (g_signal == 1)
				my_env->exit_status = 130;
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if (g_signal)
		{
			my_env->exit_status = TERMINATION_SIGINT;
			g_signal = 0;
		}
		if (ft_strlen(line) > 0)
		{
			if (!lexer(&line, my_env))
				add_history(line);
		}
		ft_free(line);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_main;

	(void)argv;
	(void)argc;
	rl_outstream = stderr;
	env_main = NULL;
	g_signal = 0;
	manage_signals(1);
	env_main = copy_env(env);
	minishell(env_main);
	return (free_env(env_main));
}
