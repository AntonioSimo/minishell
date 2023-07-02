#include "../include/minishell.h"

static void	remove_quotes(char *line)
{

}

int	is_in_quotes(char *line, int i)
{
	int j;

	j = 0;
	while (j <= i)
	{
		
	}
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void split_by_meta(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!is_in_quotes(line, i))

	}
}


void	lexer(char *line)
{
	split_by_meta(line);
}

