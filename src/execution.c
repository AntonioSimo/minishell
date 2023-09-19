#include "../include/minishell.h"

void    redir_out(t_command *cmd, int *fd)
{   
    int		fileout;
	// char	*msg;

	fileout = open(cmd->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    // dup2(fd[0], STDIN_FILENO);
	dup2(fileout, fd[0]);
	// printf("%s", msg);
	// read(fd[0], msg, O_NONBLOCK);
	close(fd[1]);
	// run_cat(env);
    exit(EXIT_SUCCESS);
}


void	test_cmd(t_command	*cmd, t_envepval *env)
{
	
	char	*path;
	
	path = find_path(cmd->command, find_expandable(env, "PATH"));
	execve(path, cmd->arguments, NULL);
	printf("chuj kurw\n");
	exit(EXIT_FAILURE);
}


void	execute_pipe(t_command *cmd, t_envepval *env, int *fd)
{	
	printf("testy\n");
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	test_cmd(cmd, env);
}

void execute_second(t_command *cmd, t_envepval *env, int *fd)
{
 //printf("at before\n");   
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    test_cmd(cmd, env);
}

void	run_commands(t_command *cmds, t_envepval *env)
{
	int		fd[2];
	pid_t	pid;

	//function so far is trying to replicate right redir
	// printf("here\n");
	if (pipe(fd) == -1)
			perror_exit("Pipe error\n");
	// while (cmds)
	// {
		pid = fork();
		if (pid == -1)
			perror_exit("Fork error\n");
		if (pid == 0)	
			execute_pipe(cmds, env, fd);
            // test_cmd(cmds, env);
		 waitpid(pid, NULL, 0);
		cmds = cmds->next;
		// pid = fork();
		// // // cmds = cmds->next;
		// // if (pid == -1)
		// // 	perror_exit("Fork error\n");
		// if (pid == 0)	
		redir_out(cmds,fd);
        // //     execute_second(cmds->next, env, fd);
		waitpid(pid, NULL, 0);
	// }
}
