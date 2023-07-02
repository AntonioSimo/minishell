#include "../include/minishell.h"

void	parse(char *line)
{
	char **splitted = ft_split(line, ' ');
	ft_printf("this is my line: %s\n", splitted[0]);
	exit(0);
}