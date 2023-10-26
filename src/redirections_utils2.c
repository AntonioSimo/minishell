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

void	execute_pipe(int **fd, t_execution *temp)
{
	close(temp->error_pipe[0]);
	if (temp->cmds_size == 1)
		return ;
	if (temp->i == 0)
	{
		close(fd[temp->i][0]);
		dup2(fd[temp->i][1], STDOUT_FILENO);
		close(fd[temp->i][1]);
	}
	else if (temp->i == temp->cmds_size - 1)
	{
		dup2(fd[temp->i - 1][0], STDIN_FILENO);
		close(fd[temp->i - 1][0]);
	}
	else
	{
		close(fd[temp->i][0]);
		dup2(fd[temp->i - 1][0], STDIN_FILENO);
		dup2(fd[temp->i][1], STDOUT_FILENO);
		close(fd[temp->i - 1][0]);
		close(fd[temp->i][1]);
	}
}
