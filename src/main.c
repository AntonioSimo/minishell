#include "../include/minishell.h"

char *get_path(char **env)
{
	int i;
	int j;
	//printf("here \n");

	i = 0;
	j = 6;
	while (env[i])
	{
		//printf("line: %s\n", env[i]);
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			while (--j)
				env[i]++;
			return (env[i]);
		}
		i++;
	}
	return (NULL);
	
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

		loop(env);	
	exit (EXIT_SUCCESS);
}
