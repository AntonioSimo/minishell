#include "../include/minishell.h"

t_token	*create_token(char *string, t_type type)
{
	t_token	*token;

	token = ptr_check(malloc(sizeof(t_token)));
	token->command = ptr_check(ft_strdup(string));
	token->type = type;
	return (token);
}

void	tokenize_space(t_list **token_lst, char *line, int *i)
{
	t_token	*token;
	//int j;

	//j = 0;
	ft_printf("space\n");
	token = create_token(" ", SEPERATOR);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	while (ft_isspace(line[*i]))
		*i += 1;
}

void	tokenize_pipe(t_list **token_lst, int *i)
{
	t_token *token;

	ft_printf("pipe\n");
	token = create_token("|", PIPE);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 1;
}

void	tokenize_redir_in(t_list **token_lst, int *i)
{
	t_token *token;

	ft_printf("redir in\n");
	token = create_token("<", REDIR_INPUT);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 1;
}

void	tokenize_redir_out(t_list **token_lst, int *i)
{
	t_token *token;

	ft_printf("redir_out\n");
	token = create_token(">", REDIR_OUTPUT);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 1;
}

void	tokenize_redir_outapp(t_list **token_lst, int *i)
{
	t_token *token;

	ft_printf("redir_out_app\n");
	token = create_token(">>", REDIR_OUTPUT_APPEND);
	ft_lstadd_back(token_lst, ft_lstnew(token));
	*i += 2;
}

void	tokenize_symbols(t_list **token_lst, char *line, int *i)
{
	if (line[*i] == '|')
		tokenize_pipe(token_lst, i);
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ft_printf("HEREDOC\n");
		*i += 2;
	}	
	else if (line[*i] == '<')
		tokenize_redir_in(token_lst, i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		tokenize_redir_outapp(token_lst, i);
	else if (line[*i] == '>')
		tokenize_redir_out(token_lst, i);
}