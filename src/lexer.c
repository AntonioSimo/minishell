#include "../include/minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void tokenize_word(t_list **token_lst, char *line, int *position)
{
	char	*word;
	int		i;
	t_token	*token;

	i = 0;
	while (line[*position + i] && !ft_strchr("|<>\'\"", line[*position + i])
			&& !ft_isspace(line[*position + i]))
		i++;
	word = ft_substr(line, *position, i);
	*position += i;
	token = create_token(word, DEFAULT);
	ft_lstadd_back(token_lst, ft_lstnew(token));
}

void	tokenize_quotted(t_list **token_lst, char *line, int *position, t_type quotes)
{
	int		quotes_len;
	char	*quotted_sentence;
	t_token	*token;

	quotes_len = strlen_quoted(line, *position, quotes);
	quotted_sentence = ptr_check(ft_substr(line, *position + 1, quotes_len));
	token = create_token(quotted_sentence, quotes);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*position += quotes_len + 2;
}

void scanner(char *line, t_list **token_lst)
{
	int i;
	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
			tokenize_quotted(token_lst, line, &i, quotes);
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
				tokenize_space(token_lst, line, &i);
			else
			{
				if (ft_strchr("|<>", line[i]))
					tokenize_symbols(token_lst, line, &i);
				else
					tokenize_word(token_lst, line, &i);
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
		scanner(line, &tokens);
		//combine_tokens(tokens);
		//check_pipes(tokens);
		//expander(tokens);
		print_list(tokens);
	}	
	else
		ft_printf("Unclosed quotes.\n");
}

