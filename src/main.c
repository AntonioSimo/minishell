/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/19 15:42:58 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_code;

void	loop(t_envepval *my_env)
{
	char *line;
	char *or_home;

	or_home = ptr_check(find_expandable(my_env, "HOME"));
	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
		{
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
	(void) env;
	t_env   *env_main;
	
	g_error_code = 0;
	
	env_main = copy_env(env);
	// print_copy_env(env_main);
	// print_my_env(my_env);
	loop(env_main->env);	
	exit (EXIT_SUCCESS);
}
