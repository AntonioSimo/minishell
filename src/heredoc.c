#include "minishell.h"

// int	heredoc(char *file)
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

// void	pipe_heredoc(t_command *command)
// {

// }

static void child_process_here_doc(char *file, int *pipe_fd)
{
    char    *line;
	char	*end_of_file = file;
    // int i;  
	if (!pipe_fd || !end_of_file)
        exit(1);
    close(pipe_fd[0]);
    while (1)
    {
       line = readline("> ");
        if (!line || ft_strcmp(line, end_of_file) == 0)
        {
            close(pipe_fd[1]);
            // ft_free_single_array(line);
			free(line);
            break;
        }
        // i = 0;
        // while (line &&line[i])
        // {
        //     if (line[i] == '$')
        //        line = ft_handle_var(line, &i, main);
        //     else
        //         i++;
        // }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
	exit (0);
}

void    ft_here_document(t_token *token, t_command *command, t_env *env)
{
    int		status;
    pid_t	child_pid;
    int		pipe_fd[2];
	(void) token;

	// if (!main || !main->token || !main->token->file)
    //     return (ft_exit_code_change(main, 9));
    if (pipe(pipe_fd) == -1)
		return ;
        // return (ft_exit_code_change(main, 9));
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    child_pid = fork();
    if (child_pid == 0)
    {
        // ft_child_signal();
        child_process_here_doc(command->redirections->lst->file, pipe_fd);
    }
    else if (child_pid > 0)
    {
        close(pipe_fd[1]);
        waitpid(child_pid, &status, 0);
        env->exit_status = status;
    }
    else
	{
        perror("fork");
	}
	close(pipe_fd[0]);
    //main->fd[0] = pipe_fd[0];
   // ft_signal();
}
