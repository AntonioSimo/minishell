#include "../include/minishell.h"

void	print_redirections(t_redir_lst	*redir)
{
	const char	*type_str[] = {
	[REDIR_INPUT] = "REDIR_INPUT",
	[HEREDOC] = "HEREDOC",
	[REDIR_OUTPUT] = "REDIR_OUTPUT",
	[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND",
	};
	while (redir)
	{
		printf("type = %-12s | str = '%s'\n", \
		type_str[redir->type], redir->file);
		redir = redir->next;
	}
}

int redir_size(t_redir_lst	*redir)
{
	int i=0;
	if (!redir)
		return(0);
	while (redir)
	{
		i++;
		redir = redir->next;
	}
	return (i);
}

t_redir_lst	*lst_redir_new(char	*file, t_type type)
{
	t_redir_lst *redir;

	redir = ptr_check(malloc(sizeof(t_redir)));
	redir->file = ptr_check(ft_strdup(file));
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_redir_lst	*redir_lst_last(t_redir_lst *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	push_redir(t_redir_lst **redir_lst, t_redir_lst *redir)
{
	t_redir_lst	*redir_node;
	
	if ((*redir_lst) == NULL)
	{
		(*redir_lst) = redir;
		return ;
	}
	redir_node = redir_lst_last((*redir_lst));
	redir_node->next = redir;
}

void	*destroy_redir(t_redir_lst *redir)
{
	t_redir_lst	*node;
	
	if (!redir)
		return (NULL);
	while (redir)
	{
		node = redir->next;
		free(redir->file);
		free(redir);
		redir = node;
	}
	return (NULL);
}
