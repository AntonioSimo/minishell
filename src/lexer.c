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
			s_quotes = !(s_quotes && d_quotes);
		if (*line == '\"')
			d_quotes = !(s_quotes && d_quotes);
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
			s_quotes = !(s_quotes && d_quotes);
		if (line[i] == '\"')
			d_quotes = !(s_quotes && d_quotes);
		i++;
	}
	if (!d_quotes)
		return (DOUBLE_QUOTED);
	else if (!s_quotes)
		return (SINGLE_QUOTED);
	else
		return (DEFAULT);

}

int	strlen_quoted(char *line, int position, t_type quotes_type)
{
	int	length;
	
	length = 0;
	position++;
	while (line[position + length])
	{
		if (quotes_type == SINGLE_QUOTED && line[position + length] == '\'')
			return (length);
		if (quotes_type == DOUBLE_QUOTED && line[position + length] == '\"')
			return (length);
		length++;
	}
	ft_printf("error quotted\n");
	return (0);
}

void check_pipes(char *line)
{
	int i;
	int	quotes_len;
	char *quotted_sentence;

	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
		{
			ft_printf("im here at %i\n", i);
			if (quotes == SINGLE_QUOTED)
				ft_printf("sq\n\n");
			if (quotes == DOUBLE_QUOTED)
				ft_printf("DQ\n");
			quotes_len = strlen_quoted(line, i, quotes);
			ft_printf("quottes len: %i\n", quotes_len);
			quotted_sentence = ft_substr(line, i + 1, quotes_len);   //make function to check null ptr and exit
			if (!quotted_sentence)    
				exit(EXIT_FAILURE);
			ft_printf("token in quotes: %s\n", quotted_sentence);
			i += quotes_len + 2;
			//ft_printf("my i is on %i position\n", i);

		}	
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
			{
				ft_printf("space!");
				while (ft_isspace(line[i]))
				{
					ft_printf("skip ");
					i++;
				}
				printf("\n");
			}
			else
			{

				if (line[i] == '|')
				{
					ft_printf("pipe\n");
				}
				else if (line[i] == '<' && line[i+1] == '<')
				{
					ft_printf("HEREDOC\n");
					i++;
				}
				else if (line[i] == '<')
				{
					ft_printf("redir in\n");
				}
				else if(line[i] == '>' && line[i+1] == '>')
				{
					ft_printf("redir out append\n");
				}
				else if(line[i] == '>')
					ft_printf("redir out\n");
				i++;
			}
			
		}
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
		//exit(EXIT_FAILURE);
	}
	check_pipes(line);
	
	//tokenize(line);
}

