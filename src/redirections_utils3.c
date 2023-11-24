/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:45:01 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	close_out(int *j, t_redir *redir)
{
	if (*j < redir->out_count)
	{
		close(redir->fileout[*j]);
		j++;
	}
}

static void	close_in(int *k, t_redir *redir)
{
	if (*k < redir->in_count)
	{
		close(redir->filein[*k]);
		k++;
	}
}

void	close_redir(t_redir *redir)
{
	int			j;
	int			k;
	t_redir_lst	*temp;

	temp = redir->lst;
	j = 0;
	k = 0;
	dup2(redir->stdout_cpy, STDOUT_FILENO);
	dup2(redir->stdin_cpy, STDIN_FILENO);
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT)
			close_out(&j, redir);
		else if (temp->type == REDIR_INPUT)
			close_in(&k, redir);
		temp = temp->next;
	}
}

int	count_redir(t_redir_lst *redir, t_type type)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	while (redir)
	{
		if ((type == REDIR_INPUT && redir->type == REDIR_INPUT)
			|| (type == REDIR_INPUT && redir->type == HEREDOC))
			in++;
		if ((type == REDIR_OUTPUT && redir->type == REDIR_OUTPUT)
			|| (type == REDIR_OUTPUT
				&& redir->type == REDIR_OUTPUT_APPEND))
			out++;
		redir = redir->next;
	}
	if (type == REDIR_INPUT)
		return (in);
	if (type == REDIR_OUTPUT)
		return (out);
	return (0);
}