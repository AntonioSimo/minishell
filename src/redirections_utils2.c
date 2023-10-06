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

static void	handle_first_cmd(int **fd, int i, int cmds_size)
{
	int	j;

	j = 0;
	close(fd[i][0]);
	dup2(fd[i][1], STDOUT_FILENO);
	while (j < cmds_size - 1)
	{
		if (j != i)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

static void	handle_last_cmd(int **fd, int i, int cmds_size)
{
	int	j;

	j = 0;
	close(fd[i - 1][1]);
	dup2(fd[i - 1][0], STDIN_FILENO);
	while (j < cmds_size - 1)
	{
		if (j != i - 1)
		{
			close(fd[j][1]);
			close(fd[j][0]);
		}
		j++;
	}
}

static void	handle_middle_cmds(int **fd, int i, int cmds_size)
{
	int	j;

	j = 0;
	dup2(fd[i - 1][0], STDIN_FILENO);
	dup2(fd[i][1], STDOUT_FILENO);
	while (j < cmds_size - 1)
	{
		if (j != i -1)
			close(fd[j][0]);
		if (j != i)
			close(fd[j][1]);
		j++;
	}
}

void	execute_pipe(int **fd, int i, t_command *head)
{
	int	cmds_size;

	cmds_size = count_cmds(head);
	if (cmds_size == 1)
		return ;
	if (i == 0)
	{
		handle_first_cmd(fd, i, cmds_size);
		return ;
	}
	if (i == cmds_size - 1)
	{
		handle_last_cmd(fd, i, cmds_size);
		return ;
	}
	handle_middle_cmds(fd, i, cmds_size);
}
