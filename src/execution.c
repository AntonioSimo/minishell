#include "../include/minishell.h"

// void    redir_out(t_command *cmd, t_env *env)
// {   
//     int		fileout;
// 	// char	*msg;

// 	fileout = open(cmd->command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     // dup2(fd[0], STDIN_FILENO);
// 	dup2(fileout, STDOUT_FILENO);
// 	// printf("%s", msg);
// 	// read(fd[0], msg, O_NONBLOCK);
// 	// find_cmd(cmd->next, env);
// 	// close(fd[1]);
// 	// run_cat(env);
//     // exit(EXIT_SUCCESS);
// }


void	find_cmd(t_command	*cmd, t_env *env)
{
	
	char	*path;
	
	// if (cmd && ft_isbuiltin(cmd->command))
	//   	exe_builtin(cmd->arguments, cmd->command, env);
	path = find_path(cmd->command, find_expandable(env->env, "PATH"));
	if (path)
	{
		execve(path, cmd->arguments, env->env_copy);
		printf("%s: command error\n", cmd->command);
	}
	else
		printf("%s: command not found\n", cmd->command);
	exit(EXIT_FAILURE);
}


void	execute_pipe(t_command *cmd, t_env *env, int *fd)
{	
	// printf("findy\n");
	// (void)cmd;
	// (void)env;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	// printf("hello from pipe!\n");
	// exit(0);
	find_cmd(cmd, env);
}

void execute_second(t_command *cmd, t_env *env, int *fd)
{
 //printf("at before\n"); 
 	// (void)cmd;
	// (void)env; 
	// char buffer[256];
	// size_t	buf_size;
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    find_cmd(cmd, env);
	// buf_size = read(fd[0], buffer, sizeof(buffer) - 1);
	// buffer[buf_size] = '\0';
	// printf("%s\n", buffer);
}

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

int	count_redir_out(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir)
	{
		if (redir->type == REDIR_OUTPUT)
			i++;
		redir = redir->next;
	}
	return (i);
}

int	count_redir_in(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
			i++;
		redir = redir->next;
	}
	return (i);
}
int	count_redir(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir)
	{
		i++;
		redir = redir->next;
	}
	return (i);
}

void	run_redirections(t_redir *redir)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	i = 0;
	redir->stdin_cpy = dup(STDIN_FILENO);
	redir->stdout_cpy = dup(STDOUT_FILENO);
	redir->fileout = ptr_check(malloc(sizeof(int) * count_redir_out(redir)));
	redir->filein = ptr_check(malloc(sizeof(int) * count_redir_in(redir)));

	// printf("redir: %i\n", count_redir(redir));
	// sleep(5);
	while (i < count_redir(redir))
	{
		if (redir->type == REDIR_OUTPUT)
		{
			redir->fileout[j] = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (redir->fileout[j] == -1)
				perror_exit("FD error\n");
			dup2(redir->fileout[j], STDOUT_FILENO);
			j++;
		}
		if (redir->type == REDIR_INPUT)
		{
			redir->filein[k] = open(redir->file, O_RDONLY);
			if (redir->filein[k] == -1)
				perror_exit("FD error\n");
			dup2(redir->filein[k], STDIN_FILENO);
			k++;
		}
		i++;
	}
}

void	close_redir(t_redir *redir)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;

	dup2(redir->stdout_cpy, STDOUT_FILENO);
	dup2(redir->stdin_cpy, STDIN_FILENO);

	while (i <count_redir(redir))
	{
		if (redir->type == REDIR_OUTPUT)
		{
			close(redir->fileout[j]);
			j++;
		}
		if (redir->type == REDIR_INPUT)
		{
			close(redir->filein[j]);
			k++;
		}
		i++;
	}
}

void	run_commands(t_command *cmds, t_env *env)
{
	int			fd[2];
	int			i;
	pid_t		*pid;
	t_command	*head;

	i = 0;
	head = cmds;
	if (count_cmds(cmds) == 1 && ft_isbuiltin(cmds->command))
	{	
			if (cmds->redirections)
				run_redirections(cmds->redirections);
			exe_builtin(cmds->arguments, cmds->command, env);
			if (cmds->redirections)
				close_redir(cmds->redirections);
			return ;
	}
	pid = ptr_check(malloc(sizeof(pid_t) * count_cmds(cmds))); //allocate array for every process
	while (cmds)
	{
		if (pipe(fd) == -1)
			return (perror_exit("Pipe error\n"));
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror_exit("Fork error\n"));
		if (pid[i] == 0)
		{

			if (cmds->redirections)
				run_redirections(cmds->redirections);
			find_cmd(cmds, env);
		}
		cmds = cmds->next;	
	}
	cmds = head;
		close(fd[0]);
		close(fd[1]);
	i = 0;
	while (i < count_cmds(cmds))
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	
		// waitpid(pid2, NULL, 0);

}
