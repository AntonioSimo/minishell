#include "minishell.h"

// int heredoc(char *file)
// {
// 	char	*line;
// 	char	*end_of_file = file;
// 	int		fd1;
// 	int		fd2;

// 	fd1 = (open("/tmp/file", O_CREAT | O_RDWR | O_TRUNC, 0644));
// 	if (fd1 == -1) 
// 	{
// 		perror("Errore durante l'apertura del file");
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL || ft_strncmp(end_of_file, line, ft_strlen(end_of_file)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd1, line, ft_strlen(line));
// 		write(fd1, "\n", 1);
// 		free(line);
// 	}
// 	fd2 = open("/tmp/file", O_RDONLY, 0644);
// 	close(fd1);
// 	return (fd2);
// }
// 
static void child_process_here_doc(char *file, int *pipe_fd)
{
    char    *maybe_command;
	// if (!pipe_fd || !main)
        // exit(1);
    close(pipe_fd[0]);
    while (1)
    {
        maybe_command = readline("> ");
        if (!maybe_command || ft_strcmp(maybe_command, file) == 0)
        {
            close(pipe_fd[1]);
            free(maybe_command);
            exit(0);
        }
        write(pipe_fd[1], maybe_command, ft_strlen(maybe_command));
        write(pipe_fd[1], "\n", 1);
        free(maybe_command);
    }
}

int heredoc(t_redir_lst *temp)
{
    int status;
    pid_t   child_pid;
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
	{
        return (write(2, "HEREDOC ERROR\n", 15));
	}
	manage_signals(0);
    child_pid = fork();
    if (child_pid == 0)
    {
        manage_signals(2);
        child_process_here_doc(temp->file, pipe_fd);
    }
    else if (child_pid > 0)
    {
        close(pipe_fd[1]);
        waitpid(child_pid, &status, 0);
        // main->exit_code = status / 256;
    }
    else
        perror("fork");
    // if (temp->fd[0] > 2)
    //     close(temp->fd[0]);
    manage_signals(3);
	return (pipe_fd[0]);
}
