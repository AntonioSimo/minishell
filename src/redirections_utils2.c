/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/10 18:58:29 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	execute_pipe(int **fd, int i, t_command *head)
{
	int	cmds_size;

	cmds_size = count_cmds(head);
	if (cmds_size == 1)
		return ;
	if (cmds_size == 2)
	{
		if (i == 0)
		{
			close(fd[0][0]);
			dup2(fd[0][1], STDOUT_FILENO);
		}
		else
		{
			close(fd[0][1]);
			dup2(fd[0][0], STDIN_FILENO);
		}
			
		return ;
	}
	else
	{
		if (i == 0)
		{
			close(fd[1][0]);
			close(fd[1][1]);
			close(fd[0][0]);
			dup2(fd[0][1], STDOUT_FILENO);
			return ;
		}
		if (i == count_cmds(head) - 1)
		{
			close(fd[1][1]);
			close(fd[1][0]);
			close(fd[0][1]);
			dup2(fd[0][0], STDIN_FILENO);
			return ;
		}
		else
		{
			dup2(fd[0][0], STDIN_FILENO);
			dup2(fd[1][1], STDOUT_FILENO);
			close(fd[0][1]);
			close(fd[1][0]);
			return ;
		}
	}
}