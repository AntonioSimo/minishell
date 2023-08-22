#include "../include/minishell.h"

static t_token	*lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token	*lstnew(char *str, t_type type)
{
	t_token	*new_node;

	new_node = ptr_check(malloc(sizeof(t_token)));
	new_node->command = ptr_check(ft_strdup(str));
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*lst_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_node = lstlast(*lst);
	lst_node->next = new;
}
