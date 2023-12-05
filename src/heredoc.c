/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 18:00:38 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_redir_lst(t_execution *temp)
{
	t_command	*cmds;
	t_redir_lst	*redir;

	cmds = temp->head;
	while (cmds)
	{
		if (cmds->redirections)
		{
			redir = cmds->redirections->lst;
			while (redir)
			{
				if (redir->type == HEREDOC)
					if (redir->fd != -1)
						close(redir->fd);
				redir = redir->next;
			}
		}
		cmds = cmds->next;
	}
}

int	init_heredoc(t_execution *temp)
{
	t_command	*cmds;
	t_redir_lst	*redir;

	cmds = temp->head;
	while (cmds)
	{
		if (cmds->redirections)
		{
			redir = cmds->redirections->lst;
			while (redir)
			{
				if (redir->type == HEREDOC)
					if (heredoc(redir) == 1)
						return (1);
				redir = redir->next;
			}
		}
		cmds = cmds->next;
	}
	return (0);
}

void	child_process_here_doc(char *file, int *pipe_fd)
{
	char	*line;
	char	*end_of_file;

	end_of_file = file;
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(end_of_file, line, \
				ft_strlen(end_of_file)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
}

static int	handle_parent_heredoc(t_redir_lst *redir, int child_pid, \
			int *pipe_fd)
{
	int	status;

	close(pipe_fd[1]);
	redir->fd = pipe_fd[0];
	waitpid(child_pid, &status, 0);
	manage_signals(3);
	if (WIFSIGNALED(status))
		return (1);
	return (0);
}

int	heredoc(t_redir_lst *redir)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (write(2, "HEREDOC ERROR\n", 15));
	manage_signals(0);
	child_pid = fork();
	if (child_pid < 0)
		return (write(2, "HEREDOC FORK ERROR\n", 20));
	if (child_pid == 0)
	{
		manage_signals(2);
		child_process_here_doc(redir->file, pipe_fd);
		exit (EXIT_SUCCESS);
	}
	else if (child_pid > 0)
	{
		if (handle_parent_heredoc(redir, child_pid, pipe_fd) == 0)
			return (0);
	}
	else
		perror("fork");
	return (0);
}
