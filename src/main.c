/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/11 17:01:46 by pskrucha         ###   ########.fr       */
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
		// rl_on_new_line();
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
			break ;
		add_history(line);
		lexer(line, my_env, or_home);
		ft_free(line);
	}
}	

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_envepval	*my_env;

	g_error_code = 0;
	my_env = NULL;
	//char **str = NULL;
	
	
	//str=str_join_2d(str, "HELLO");
	//int i=0;
//	str = str_join_2d(str, NULL);
	
//	while(str[i])
//	{
//		printf("%s\n", str[i]);
//		i++;
//	}
	echo_command(argc, argv);
	//printf("%lu\n",strlen(NULL));
	set_env(&my_env, env);
	// print_my_env(my_env);
	//loop(my_env);	
	exit (EXIT_SUCCESS);
}
