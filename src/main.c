#include "../include/minishell.h"

void	set_env(t_list	*my_env, char **env)
{
	int i;
	t_envepval	*temp;

	i = 0;
	while (env[i])
	{
		
	}
}

void	loop(char **env)
{
	char *line;

	(void)env;
	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
			break ;
		add_history(line);
		lexer(line);
		free(line);
	}
}	

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_list	*my_env;

	set_env(my_env, env);


	

		loop(env);	
	exit (EXIT_SUCCESS);
}
