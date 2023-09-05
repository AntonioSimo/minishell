/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 14:32:04 by asimone       #+#    #+#                 */
/*   Updated: 2023/09/05 11:54:43 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	loop(char **env, t_envepval *my_env)
{
	char *line;

	(void) my_env;
	(void)env;
	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
			break ;
		add_history(line);
		ft_free(line);
	}
}	

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_envepval	*my_env = NULL;

	loop(env, my_env);	
	exit (EXIT_SUCCESS);
}