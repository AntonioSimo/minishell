#include "../include/minishell.h"

t_token	*create_token(char *string, t_type type)
{
	t_token	*token;

	token = ptr_check(malloc(sizeof(t_token)));
	token->command = ptr_check(ft_strdup(string));
	token->type = type;
	return (token);
}

static void	print_token(void *data)
{
	t_token		*token;
	const char	*type_str[] = {
	[DEFAULT] = "DEFAULT",
	[SINGLE_QUOTED] = "SINGLE_QUOTED",
	[DOUBLE_QUOTED] = "DOUBLE_QUOTED",
	[REDIR_INPUT] = "REDIR_INPUT",
	[HEREDOC] = "HEREDOC",
	[REDIR_OUTPUT] = "REDIR_OUTPUT",
	[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND",
	[PIPE] = "PIPE",
	[SEPERATOR] = "SEPERATOR",
	};

	token = data;
	printf("type = %-12s | str = '%s'\n", \
	type_str[token->type], token->command);
}

void	print_list(t_list *token_lst)
{
	while (token_lst)
	{
		print_token(token_lst->content);
		token_lst = token_lst->next;
	}
}