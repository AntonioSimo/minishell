/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 17:23:52 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_redir_lst	*lst_redir_new(char	*file, t_type type)
{
	t_redir_lst	*redir;

	redir = ptr_check(malloc(sizeof(t_redir_lst)));
	redir->file = ptr_check(ft_strdup(file));
	redir->type = type;
	redir->fd = -1;
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
