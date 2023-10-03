/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/21 16:55:37 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_code;

void	loop(t_env *my_env)
{
	char *line;
	char *or_home;

	or_home = ptr_check(find_expandable(my_env->env, "HOME"));
	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		if (ft_strlen(line) > 0)
			lexer(line, my_env, or_home);
		ft_free(line);
		rl_on_new_line();
	}
}	

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_env   *env_main;
	
	g_error_code = 0;
	env_main = NULL;
	copy_env(env, &env_main);
	signal(SIGINT, signal_int_handler);
	signal(SIGQUIT, SIG_IGN);
	loop(env_main);	
	exit (EXIT_SUCCESS);
}

