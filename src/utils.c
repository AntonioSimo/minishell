#include "../include/minishell.h"

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