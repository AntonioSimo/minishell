#include "../include/minishell.h"

static t_token	*last_token(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token	*lst_token_new(char *str, t_type type)
{
	t_token	*new_node;

	new_node = ptr_check(malloc(sizeof(t_token)));
	new_node->command = ptr_check(ft_strdup(str));
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	push_token(t_token **lst, t_token *new)
{
	t_token	*lst_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_node = last_token(*lst);
	lst_node->next = new;
}

void	print_tokens(t_token *token_lst)
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

	while (token_lst)
	{
		token = token_lst;
		printf("type = %-12s | str = '%s'\n", \
		type_str[token->type], token->command);
		token_lst = token_lst->next;
	}
	printf("\n");
}

void	destroy_tokens(t_token	*tokens)
{
	t_token *temp;
	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens->next;
		free(tokens->command);
		free(tokens);
		tokens = temp;;
	}
	tokens = NULL;
}
