/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 14:51:26 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_access_out(t_redir_lst *temp)
{
	if (access(temp->file, W_OK) == -1 && access(temp->file, F_OK) == 00)
	{
		ft_print_message("mustash: ", temp->file, \
		": Permission denied\n", STDERR_FILENO);
		return (1);
	}
	if (access(temp->file, F_OK) != 00)
	{
		ft_print_message("mustash: ", temp->file, \
		": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	handle_redir_out(t_redir_lst *temp, t_redir *redir)
{
	static int	i = 0;

	if (temp->type == REDIR_OUTPUT)
		redir->fileout[i] = open(temp->file, O_WRONLY \
						| O_CREAT | O_TRUNC, 0644);
	else if (temp->type == REDIR_OUTPUT_APPEND)
		redir->fileout[i] = open(temp->file, O_WRONLY \
						| O_CREAT | O_APPEND, 0644);
	if (check_access_out(temp))
		return (1);
	if (redir->fileout[i] == -1)
		perror_exit("FD error\n");
	dup2(redir->fileout[i], STDOUT_FILENO);
	close(redir->fileout[i]);
	redir->out_count++;
	i++;
	return (0);
}

int	check_access_in(t_redir_lst *temp)
{
	if (access(temp->file, R_OK) == -1 && access(temp->file, F_OK) == 00)
	{
		ft_print_message("mustash: ", temp->file, \
		": Permission denied\n", STDERR_FILENO);
		return (1);
	}
	if (access(temp->file, F_OK) != 00 && temp->type != HEREDOC)
	{
		ft_print_message("mustash: ", temp->file, \
		": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	handle_redir_in(t_redir_lst *temp, t_redir *redir)
{
	static int	j = 0;

	if (temp->type == REDIR_INPUT)
		redir->filein[j] = open(temp->file, O_RDONLY);
	else if (temp->type == HEREDOC)
	{
		// dup2(redir->filein[j], STDIN_FILENO);
		// close(redir->filein[j]);
	}
	if (check_access_in(temp))
		return (1);
	if (redir->filein[j] == -1)
		perror_exit("FD error\n");
	dup2(redir->filein[j], STDIN_FILENO);
	close(redir->filein[j]);
	redir->in_count++;
	j++;
	return (0);
}

int	run_redirections(t_redir *redir, t_env *env)
{
	t_redir_lst	*temp;

	temp = redir->lst;
	alloc_in_n_out(&redir);
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APPEND)
		{
			if (handle_redir_out(temp, redir))
			{
				env->exit_status = ERROR;
				return (ERROR);
			}
		}
		else if (temp->type == REDIR_INPUT || temp->type == HEREDOC)
		{
			if (handle_redir_in(temp, redir))
			{
				env->exit_status = ERROR;
				return (ERROR);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
