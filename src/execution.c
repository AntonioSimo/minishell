#include "../include/minishell.h"

void    redir_out(t_command *cmd, t_env *env)
{   
    int		fileout;
	// char	*msg;

	fileout = open(cmd->command, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	// printf("%s", msg);
	// read(fd[0], msg, O_NONBLOCK);
	find_cmd(cmd->next, env);
	// close(fd[1]);
	// run_cat(env);
    exit(EXIT_SUCCESS);
}


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

void	run_commands(t_command *cmds, t_env *env)
{
	int		fd[2];
	pid_t	pid1;
	// pid_t	pid2;
	//function so far is trying to replicate right redir
	// printf("here\n");
	while (cmds)
	{
		if (ft_isbuiltin(cmds->command))
		{
			exe_builtin(cmds->arguments, cmds->command, env);
			cmds = cmds->next;
		}
		else 
		{
			if (pipe(fd) == -1)
				return (perror_exit("Pipe error\n"));
			pid1 = fork();
			if (pid1 == -1)
				return (perror_exit("Fork error\n"));
			if (pid1 == 0)	
				find_cmd(cmds, env);
			// cmds = cmds->next;

			// redir_out(cmds, env);
			// execute_pipe(cmds, env, fd);
		//  waitpid(pid1, NULL, 0);
		// cmds = cmds->next;
		// pid = fork();
		// // // cmds = cmds->next;
		// // if (pid == -1)
		// // 	perror_exit("Fork error\n");
		// if (pid == 0)	

		// pid2 = fork();
		// if (pid2 == 0)
        // 	execute_second(cmds->next, env, fd);
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, NULL, 0);
		}
		// waitpid(pid2, NULL, 0);
	}
}
