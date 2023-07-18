#include "../include/minishell.h"

void	skip_quotes(char *line, int *i, t_type *quotes)
{
	int	quotted_len;

	quotted_len = strlen_quoted(line, *i, *quotes);
	ft_printf("quoted len: %i \n", quotted_len);
	*i += quotted_len + 2;
	*quotes = DEFAULT;

}

void	scanner(char *line)
{
	int i;
	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
			skip_quotes(line, &i, &quotes);
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
			{
				while (ft_isspace(line[i]))
					i += 1;
			}
			else
			
			{
				if (ft_strchr("|<>", line[i]))
				{
					//check_redirections(line, &i);
					ft_printf("i: %i\n", i);
					i++;
				}
				else
					i++;
			}
		}
	}
}

void	lexer(char *line)
{
	bool quotes;
	t_list	*tokens;

	tokens = NULL;	
	quotes = check_quotes(line);
	if (quotes)
	{
		//scanner(line);
		tokenize(line, &tokens);
		//combine_tokens(tokens);
		//check_pipes(tokens);
		//expander(tokens);
		print_list(tokens);
	}	
	else
		ft_printf("Unclosed quotes.\n");
}

