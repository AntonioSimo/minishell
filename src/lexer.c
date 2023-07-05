#include "../include/minishell.h"

//static void	remove_quotes(char *line)
//{

//}

//int	is_in_quotes(char *line, int i)
//{
//	int j;
//	(void)line;

//	j = 0;
//	while (j <= i)
//	{
		
//	}
//}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

//void split_by_meta(char *line)
//{
//	int i;

//	i = 0;
//	while (line[i])
//	{
//		if (!is_in_quotes(line, i))

//	}
//}

bool check_quotes(char *line)
{
	bool d_quotes;
	bool s_quotes;

	d_quotes = true;
	s_quotes = true;
	while (*line)
	{
		if (*line == '\'')
			s_quotes = ! s_quotes && d_quotes;
		if (*line == '\"')
			d_quotes = ! s_quotes && d_quotes;
		line++;
	}
	return (d_quotes && s_quotes);
}

void	lexer(char *line)
{
	//split_by_meta(line);
	//ft_printf("%s", line);
	bool quotes = check_quotes(line);
	if (quotes)
		ft_printf("closed\n");
	else
		ft_printf("opened\n");
}

