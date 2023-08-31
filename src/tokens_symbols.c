#include "../include/minishell.h"

void	tokenize_pipe(t_token **token_lst, int *i)
{
	lstadd_back(token_lst, lstnew("|", PIPE));
	*i += 1;
}

void	tokenize_redir_in(t_token **token_lst, int *i)
{
	lstadd_back(token_lst, lstnew("<", REDIR_INPUT));
	*i += 1;
}

void	tokenize_redir_out(t_token **token_lst, int *i)
{
	lstadd_back(token_lst, lstnew(">", REDIR_OUTPUT));
	*i += 1;
}

void	tokenize_redir_outapp(t_token **token_lst, int *i)
{
	lstadd_back(token_lst, lstnew(">>", REDIR_OUTPUT_APPEND));
	*i += 2;
}

void	tokenize_heredoc(t_token **token_lst, int *i)
{
	lstadd_back(token_lst, lstnew("<<", HEREDOC));
	*i += 2;
}