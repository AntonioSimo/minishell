/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 17:17:34 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_stdout_stdin(t_redir *redir)
{
	dup2(redir->stdout_cpy, STDOUT_FILENO);
	dup2(redir->stdin_cpy, STDIN_FILENO);
}

int	count_redir(t_redir_lst *redir, t_type type)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	while (redir)
	{
		if ((type == REDIR_INPUT && redir->type == REDIR_INPUT))
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
