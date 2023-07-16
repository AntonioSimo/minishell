#include "../include/minishell.h"

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

		loop(env);	
	exit (EXIT_SUCCESS);
}
