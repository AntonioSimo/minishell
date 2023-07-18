#include "../include/minishell.h"

void	tokenize_space(t_list **token_lst, char *line, int *i)
{
	t_token	*token;

	token = create_token(" ", SEPERATOR);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	while (ft_isspace(line[*i]))
		*i += 1;
}

void	tokenize_pipe(t_list **token_lst, int *i)
{
	t_token *token;

	token = create_token("|", PIPE);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 1;
}

void	tokenize_redir_in(t_list **token_lst, int *i)
{
	t_token *token;

	token = create_token("<", REDIR_INPUT);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 1;
}

void	tokenize_redir_out(t_list **token_lst, int *i)
{
	t_token *token;

	token = create_token(">", REDIR_OUTPUT);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 1;
}

void	tokenize_redir_outapp(t_list **token_lst, int *i)
{
	t_token *token;

	token = create_token(">>", REDIR_OUTPUT_APPEND);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 2;
}

void	tokenize_heredoc(t_list **token_lst, int *i)
{
	t_token *token;

	token = create_token("<<", HEREDOC);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 2;
}

void	tokenize_symbols(t_list **token_lst, char *line, int *i)
{
	if (line[*i] == '|')
		tokenize_pipe(token_lst, i);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		tokenize_heredoc(token_lst, i);
	else if (line[*i] == '<')
		tokenize_redir_in(token_lst, i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		tokenize_redir_outapp(token_lst, i);
	else if (line[*i] == '>')
		tokenize_redir_out(token_lst, i);
}

void	tokenize_word(t_list **token_lst, char *line, int *position)
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

void tokenize(char *line, t_list **token_lst)
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