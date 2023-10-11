/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:52:43 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signal = 0;

void	loop(t_env *my_env)
{
	char	*line;

	while (1)
	{
		//ft_signal(my_env);
		//printf("loop.sign")
//		printf("hello");
		my_env->exit_status = g_signal;
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		if (ft_strlen(line) > 0)
			lexer(line, my_env);
		ft_free(line);
		rl_on_new_line();
		g_signal = SUCCESS;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_main;

	(void)argv;
	(void)argc;
	env_main = NULL;
	copy_env(env, &env_main);
	ft_signal(env_main);
	signal(SIGINT, signal_int_handler);
	// signal(SIGQUIT, SIG_IGN);
	loop(env_main);
	exit (EXIT_SUCCESS);
}
