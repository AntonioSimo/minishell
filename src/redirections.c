/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:57:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		{
			if (redir->fileout[j])
			{
				close(redir->fileout[j]);
				j++;
			}
		}
		else if (temp->type == REDIR_INPUT)
		{
			if (redir->filein[k])
			{
				close(redir->filein[j]);
				k++;
			}
		}
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

static int	handle_redir_out(t_redir_lst *temp, t_redir *redir, int *error_pipe)
{
	static int	i = 0;

	if (temp->type == REDIR_OUTPUT)
		redir->fileout[i] = open(temp->file, O_WRONLY \
						| O_CREAT | O_TRUNC, 0644);
	else if (temp->type == REDIR_OUTPUT_APPEND)
		redir->fileout[i] = open(temp->file, O_WRONLY \
						| O_CREAT | O_APPEND, 0644);
	if (access(temp->file, W_OK) == -1 && access(temp->file, F_OK) == 00)
	{
		ft_print_message("mustash: ", temp->file, ": Permission denied\n", \
			error_pipe[1]);
		return (1);
	}
	if (access(temp->file, F_OK) != 00)
	{
		ft_print_message("mustash: ", temp->file, \
		": No such file or directory\n", error_pipe[1]);
		return (1);
	}
	if (redir->fileout[i] == -1)
		perror_exit("FD error\n");
	dup2(redir->fileout[i], STDOUT_FILENO);
	i++;
	return (0);
}

static int	ft_check_permission(t_redir_lst *temp, int *error_pipe)
{
	int tmp = *(error_pipe) + 1;
	printf("Chechk permission: %i\n", tmp);
	//(void) error_pipe;
	if (access(temp->file, R_OK) == -1 && access(temp->file, F_OK) == 00)
	{
			ft_print_message("mustash: ", temp->file, ": Permission denied\n", 2);
			return (1);
	} 
	if (access(temp->file, F_OK) != 00)
	{
		//int a = *(error_pipe + 1);
		//ft_print_message("mustash: ", temp->file, ": No such file or directory\n", *(error_pipe)[1]);
		return (1);
	}
	return (0);
}

static int	handle_redir_in(t_redir_lst *temp, t_redir *redir, int *error_pipe)
{
	static int	j = 0;
	int return_value = 0;

	if (temp->type == HEREDOC)
	{
	 	redir->filein[j] = heredoc(temp->file);
		//return_value = ft_check_permission(temp, error_pipe);
	}
	if (temp->type == REDIR_INPUT)
	{
		redir->filein[j] = open(temp->file, O_RDONLY);
		return_value = ft_check_permission(temp, error_pipe);
	}
		//open(temp->file, __O_TMPFILE | O_RDWR);
	if (redir->filein[j] == -1)
		perror_exit("FD error\n");
	dup2(redir->filein[j], STDIN_FILENO);
	j++;
	return (return_value);
}

int	run_redirections(t_redir *redir, t_env *env, int *error_pipe)
{
	t_redir_lst	*temp;

	temp = redir->lst;
	redir->fileout = ptr_check(malloc(sizeof(int) \
					* count_redir(temp, REDIR_OUTPUT)));
	redir->filein = ptr_check((malloc(sizeof(int) \
					* count_redir(temp, REDIR_INPUT))));
	while (temp)
	{
		if (temp->type == REDIR_INPUT || temp->type == HEREDOC)
		{
			if (handle_redir_in(temp, redir, error_pipe))
			{
				env->exit_status = ERROR;
				return (ERROR);
			}
		}
		else if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APPEND)
		{
			if (handle_redir_out(temp, redir, error_pipe))
			{
				env->exit_status = ERROR;
				return (ERROR);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
