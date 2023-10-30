/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 18:39:23 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signal;

void	minishell(t_env *my_env)
{
	char	*line;

	while (1)
	{
		//manage_signals(1);
		line = readline(GREEN BOLD "mustash> "RESET);
		// manage_signals(0);
		if (!line)
		{
			if (g_signal == 1)
				my_env->exit_status = 130;
			printf("exit\n");
			break ;
		}
		add_history(line);
		if (g_signal)
		{
			my_env->exit_status = TERMINATION_SIGINT;
			g_signal = 0;
		}
		if (ft_strlen(line) > 0)
			lexer(line, my_env);
		ft_free(line);
		if (g_signal)
			printf("\n");
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env   *env_main;

	(void)argv;
	(void)argc;
	env_main = NULL;
	g_signal = 0;
	manage_signals(1);
	copy_env(env, &env_main);
	minishell(env_main);
	exit (env_main->exit_status);
}
