/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/13 16:12:47 by pskrucha         ###   ########.fr       */
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
	(void) env;
	t_envepval	*my_env;
	// char **str = NULL;
	// char *str1 = NULL;

	// str = push_str_2d(str, str1);
	// str = push_str_2d(str, "Hello");
	// str = push_str_2d(str, "Hello");
	// str = push_str_2d(str, "Hello");
	// str = double_free(str);
	// str = get_command(str);
	// str = double_free(str);
	// if (str[1])
	// 	printf("chuj\n");
	
	g_error_code = 0;
	my_env = NULL;
	set_env(&my_env, env);
	loop(my_env);	
	exit (EXIT_SUCCESS);
}
