
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 18:02:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc(t_execution *temp)
{
	t_command	*cmds;
	t_redir_lst *redir;

	cmds = temp->head;
	while (cmds)
	{
		redir = cmds->redirections->lst;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->fd[0] = heredoc(redir);
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}
	return (0);
}

static int child_process_here_doc(char *file)
{
	char	*line;
	char	*end_of_file = file;
	int		fd1;
	int		fd2;

 	fd1 = (open("/tmp/file", O_CREAT | O_RDWR | O_TRUNC, 0644));
	if (fd1 == -1) 
	{
		perror("Error pipe\n");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(end_of_file, line, ft_strlen(end_of_file)) == 0)
		{
			free(line);
			break ;
		}
		write(fd1, line, ft_strlen(line));
		write(fd1, "\n", 1);
		free(line);
	}
	fd2 = open("/tmp/file", O_RDONLY, 0644);
	close(fd1);
	return (fd2);
}

int heredoc(t_redir_lst *temp)
{
	int		status;
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
		pipe_fd[0] = child_process_here_doc(temp->file);
		exit (EXIT_SUCCESS);
	}
	else if (child_pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(child_pid, &status, 0);
	}
	else
	{
		//close(pipe_fd[0]);
		perror("fork");
	}
	manage_signals(3);
	return (pipe_fd[0]);
}


//static void	st_child_process(int pipe_fd[2], char *file)
//{
//	char	*text;

//	signal(SIGINT, SIG_DFL);
//	text = child_process_here_doc(file);
//	ft_putstr_fd(text, pipe_fd[1]);
//	free(text);
//	close(pipe_fd[1]);
//	exit(EXIT_SUCCESS);
//}
