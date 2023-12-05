/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 16:58:59 by asimone          ###   ########.fr       */
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

int	handle_redir_out(t_redir_lst *temp)
{
	int	fd_out;

	fd_out = 0;
	if (temp->type == REDIR_OUTPUT)
		fd_out = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (temp->type == REDIR_OUTPUT_APPEND)
		fd_out = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (check_access_out(temp))
		return (1);
	if (fd_out == -1)
		perror_exit("FD error\n");
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
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

int	handle_redir_in(t_redir_lst *temp)
{
	int	fd_in;

	fd_in = 0;
	if (temp->type == REDIR_INPUT)
	{
		if (check_access_in(temp))
			return (1);
		fd_in = open(temp->file, O_RDONLY);
		if (fd_in == -1)
			perror_exit("FD error\n");
	}
	else if (temp->type == HEREDOC)
		fd_in = temp->fd;
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

int	run_redirections(t_redir *redir, t_env *env)
{
	t_redir_lst	*temp;

	temp = redir->lst;
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APPEND)
		{
			if (handle_redir_out(temp))
			{
				env->exit_status = ERROR;
				return (ERROR);
			}
		}
		else if (temp->type == REDIR_INPUT || temp->type == HEREDOC)
		{
			if (handle_redir_in(temp))
			{
				env->exit_status = ERROR;
				return (ERROR);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
