#include "../include/minishell.h"

/**
* @brief	This function replicate the behavior of ls command
* @param environment it needs to pass the environment of the shell
* @return 0 if it work correct otherwise will return a standard Error.
*/
int	execute_ls(char **environment)
{
	pid_t	pid;
	int		val;
	int		status;

	char	*argv[] = {"/bin/ls", NULL};
	pid = fork();

	if (pid == 0)
	{
		val = execve(argv[0], argv, environment);
		if (val == -1)
			perror("Error");
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("Fork error");
		return (-1);
	}
	return (0);
}