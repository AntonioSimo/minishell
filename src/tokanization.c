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