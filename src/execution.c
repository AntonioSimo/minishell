#include "../include/minishell.h"

int	count_cmds(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}
void	find_cmd(t_command	*cmd, t_env *env)
{
	char	*path;

	path = find_path(cmd->command, find_expandable(env->env, "PATH"));
	if (path)
		execve(path, cmd->arguments, env->env_copy);
	else
		printf("%s: command not found\n", cmd->command);
	exit(EXIT_FAILURE);
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

void	run_redirections(t_redir *redir)
{
	int	j;
	int	k;
	t_redir_lst	*temp;

	j = 0;
	k = 0;
	temp = redir->lst;
	redir->fileout = ptr_check(malloc(sizeof(int) * count_redir(temp, REDIR_OUTPUT)));
	redir->filein = ptr_check((malloc(sizeof(int) * count_redir(temp, REDIR_INPUT))));
	redir->stdin_cpy = dup(STDIN_FILENO);
	redir->stdout_cpy = dup(STDOUT_FILENO);
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APPEND)
		{
			if (temp->type == REDIR_OUTPUT)
				redir->fileout[j] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (temp->type == REDIR_OUTPUT_APPEND)
				redir->fileout[j] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir->fileout[j] == -1)
				perror_exit("FD error\n");
			dup2(redir->fileout[j], STDOUT_FILENO);
			j++;
		}
		else if (temp->type == REDIR_INPUT)
		{
			redir->filein[k] = open(temp->file, O_RDONLY);
			if (redir->filein[k] == -1)
				perror_exit("FD error\n");
			dup2(redir->filein[k], STDIN_FILENO);
			k++;
		}
		temp = temp->next;
	}
}

void	close_redir(t_redir *redir)
{
	int	j;
	int	k;
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
			close(redir->fileout[j]);
			j++;
		}
		else if (temp->type == REDIR_INPUT)
		{
			close(redir->filein[j]);
			k++;
		}
		temp = temp->next;
	}
}

void	execute_pipe(int **fd, int i, t_command *head, t_command *cmd)
{
	int	j;
	int	cmds_size;
	(void)cmd;

	cmds_size = count_cmds(head);
	j = 0;
	if (cmds_size == 1)
		return ;
	if (i == 0)
	{
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
		return ;
	}
	if (i == cmds_size - 1)
	{
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
		return ;
	}
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

void	run_commands(t_command *cmds, t_env *env)
{
	int			**fd;
	int			i;
	pid_t		*pid;
	t_command	*head;

	i = 0;
	head = cmds;
	fd = NULL;
	if (count_cmds(cmds) == 1 && ft_isbuiltin(cmds->command))
	{	
			if (cmds->redirections)
				run_redirections(cmds->redirections);
			exe_builtin(cmds->arguments, cmds->command, env);
			if (cmds->redirections)
				close_redir(cmds->redirections);
			return ;
	}
	pid = ptr_check(malloc(sizeof(pid_t) * count_cmds(cmds)));
	if (count_cmds(cmds) > 1)
		fd = ptr_check(malloc(sizeof(int *) * count_cmds(cmds) - 1));
	while (i < count_cmds(cmds) - 1)
	{
		fd[i] = ptr_check(ft_calloc(2, sizeof(int)));
		if (pipe(fd[i]) == -1)
			return (perror_exit("Pipe error\n"));
		i++;
	}
	i = 0;
	while (cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror_exit("Fork error\n"));
		if (pid[i] == 0)
		{
			execute_pipe(fd, i, head, cmds);
			if (cmds->redirections)
				run_redirections(cmds->redirections);
			find_cmd(cmds, env);
		}
		i++;
		cmds = cmds->next;	
	}
	cmds = head;
	i = 0;
	while (i < count_cmds(cmds))
	{	
		if (i < count_cmds(cmds) - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
