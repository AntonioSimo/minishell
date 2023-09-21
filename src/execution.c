#include "../include/minishell.h"

extern int g_error_code;

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
	printf("%s: command not found\n", cmd->command);
}


void	execute_pipe(t_command *cmd, t_envepval *env, int *fd)
{	
	// printf("testy\n");
	// (void)cmd;
	// (void)env;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	// printf("hello from pipe!\n");
	// exit(0);
	test_cmd(cmd, env);
}

void execute_second(t_command *cmd, t_envepval *env, int *fd)
{
 //printf("at before\n"); 
 	// (void)cmd;
	// (void)env; 
	// char buffer[256];
	// size_t	buf_size;
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    test_cmd(cmd, env);
	// buf_size = read(fd[0], buffer, sizeof(buffer) - 1);
	// buffer[buf_size] = '\0';
	// printf("%s\n", buffer);
}

void	redir_in(t_command *cmd, t_envepval *env, int *fd)
{
	int	file;

	file = open(cmd->command, O_RDONLY);
	close(fd[1]);
	dup2(file, STDIN_FILENO);
	test_cmd(cmd->next, env);
}

void	run_commands(t_command *cmds, t_envepval *env)
{
	// int		fd[2];
	pid_t	pid1;
	// pid_t	pid2;
	//function so far is trying to replicate right redir
	// printf("here\n");
	// if (pipe(fd) == -1)
	// 		perror_exit("Pipe error\n");
	// while (cmds)
	// {
		pid1 = fork();
		if (pid1 == -1)
			perror_exit("Fork error\n");
		if (pid1 == 0)	
		{

			// redir_in(cmds, env, fd);
			// execute_pipe(cmds, env, fd);
		    test_cmd(cmds, env);
			g_error_code = 127;
			exit(127);
		}
		//  waitpid(pid1, NULL, 0);
		// cmds = cmds->next;
		// pid = fork();
		// // // cmds = cmds->next;
		// // if (pid == -1)
		// // 	perror_exit("Fork error\n");
		// if (pid == 0)	
		// redir_out(cmds,fd);

		// pid2 = fork();
		// if (pid2 == 0)
        // 	execute_second(cmds->next, env, fd);
		// close(fd[0]);
		// close(fd[1]);
		waitpid(pid1, NULL, 0);
		// waitpid(pid2, NULL, 0);
	// }
}
