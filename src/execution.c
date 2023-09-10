#include "../include/minishell.h"

void    redir_out(t_command *cmd, int *fd)
{   
    int		fileout;

	fileout = open(cmd->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
    exit(EXIT_SUCCESS);
}


void	test_cmd(t_command	*cmd, t_envepval *env)
{
	
	char	*path;
	
	path = find_path(cmd->command, find_expandable(env, "PATH"));
	printf("path: %s\n", path);
	execve(path, cmd->arguments, NULL);
		
	printf("chuj kurw\n");
	exit(EXIT_FAILURE);
}


void	execute_pipe(t_command *cmd, t_envepval *env, int *fd)
{	
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	
	test_cmd(cmd, env);
}

void	run_commands(t_command *cmds, t_envepval *env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
			perror_exit("Pipe error\n");
	while (cmds)
	{
		pid = fork();
		if (pid == -1)
			perror_exit("Fork error\n");
		if (pid == 0)	
		{
            if
        }
		waitpid(pid, NULL, 0);
		cmds = cmds->next;
	}
}
