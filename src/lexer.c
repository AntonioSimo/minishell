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

//int	find_here_doc(char* line, int position)
//{
//	int len;

//	len = ft_strlen(line+position);
//	if (len > 1)
//}

//t_type set_state(char *line, int position)
//{
//	t_type state;

//	if (find_here_doc(line, position))
//		return (HEREDOC);
//	if (find_pipe(line, position))
//		return (PIPE);
//	if (find_redir_out(line, position))
//		return (REDIR_OUTPUT);
//	if (find_redit_out_app(line, position))
//		return (REDIR_OUTPUT_APPEND);
//	if (find_redir_in(line, position))
//		return (REDIR_INPUT);
//}

//void tokenize(char *line)
//{
//	int i;
//	t_type state;

//	i = 0;
//	while(line[i])
//	{
//		if (state == DEFAULT)
//		{

//		}

//		i++;
//	}
//	ft_printf("len: %i", i);
//}

t_type	quotes_type(char *line, int pos)
{
	bool d_quotes;
	bool s_quotes;
	int	i;

	i = 0;
	d_quotes = true;
	s_quotes = true;
	while (i <= pos)
	{
		if (line[i] == '\'')
			s_quotes = ! s_quotes && d_quotes;
		if (line[i] == '\"')
			d_quotes = ! s_quotes && d_quotes;
		i++;
	}
	if (!d_quotes)
		return (DOUBLE_QUOTED);
	else if (!s_quotes)
		return (SINGLE_QUOTED);
	else
		return (DEFAULT);

}

void check_pipes(char *line)
{
	int i;

	t_type	quotes;

	quotes = DEFAULT;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quotes = quotes_type(line, i);
		//if (quotes == SINGLE_QUOTED)
		//	ft_printf("single_quotes at %i\n",i);
		//if (quotes == DOUBLE_QUOTED)
		//	ft_printf("double_quotes at %i\n",i);
		if (quotes == DEFAULT)
		{
			if (line[i] == '|' && ft_strlen(line + i) > 1)
				ft_printf("pipe!\n");
		}
		i++;
	}
}

void	lexer(char *line)
{
	//split_by_meta(line);
	//ft_printf("%s", line);
	
	bool quotes = check_quotes(line);
	if (quotes)
		ft_printf("closed\n");
	else
	{
		ft_printf("Unclosed quotes.\n");
		exit(EXIT_FAILURE);
	}
	check_pipes(line);
	//tokenize(line);
}

