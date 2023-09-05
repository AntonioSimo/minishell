/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 14:32:04 by asimone       #+#    #+#                 */
/*   Updated: 2023/09/05 12:42:29 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_path(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
	
}

int execute_command(char **arguments, char **environment)
{
	pid_t pid;
	int childStatus;

    if (access(arguments[0], F_OK | X_OK) != -1) 
	{ 
        pid = fork();
        if (pid == 0) 
		{
			ft_printf("%s", arguments[0]);
            execve(arguments[0], arguments, environment);
            //perror("Errore nell'esecuzione di execve");
            //exit(1);
        } 
		else if (pid > 0) 
		{
            waitpid(pid, &childStatus, 0);
            if (WIFEXITED(childStatus)) 
			{
                int exitStatus = WEXITSTATUS(childStatus);
                printf("Processo figlio terminato con stato di uscita: %d\n", exitStatus);
            }
        } 
		else 
		{
            perror("Errore nella creazione del processo figlio");
            return (1);
        }
    }
	else
        printf("Il file o il percorso non è disponibile.\n");
    return (0);
}

char **add_command_to_path(char **path, char *command)
{
    int count;
    int i;
	char **new_path;

	i = 0;
	count = 0;
    while (path[count] != NULL)
        count++;
    new_path = malloc((count + 2) * sizeof(char *));
    if (!new_path)
        exit(EXIT_FAILURE);
    while (i < count)
	{
        new_path[i] = path[i];
		i++;
	}
    new_path[i] = command;
    //new_path[i + 1] = NULL;
    free(path);
    return (new_path);
}

//void	loop(char **env)
//{
//	char	*line;
//	char	**args;
//	char	*path;

//	path = get_path(env);
//	while (1)
//	{
//	line = readline(GREEN BOLD "mustash> "RESET);
//	args = ft_split(line, ' ');
//	add_history(line);
//		if (!ft_strncmp("ls", *args, 3))
//			execute_ls(env);
//		if (!ft_strncmp("pwd", *args, 4))
//			get_current_working_dir();
//		if (!ft_strncmp("cd", *args, 3))
//			execute_cd(*args);
//		//if (!ft_strncmp("clear", *args, 6))
//		//{
//		//	clearScreen();
//		//}
//		else if (!ft_strncmp("exit", *args, 5))
//			exit(EXIT_SUCCESS);
//	}
//	free(line);
//	free(args);
//}	

void	ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	loop(char **env, t_envepval *my_env)
{
	char *line;

	(void) my_env;
	(void)env;
	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
			break ;
		add_history(line);
		ft_free(line);
	}
}	

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_envepval	*my_env = NULL;

	printf("%s", *env);

	char *path = get_path(env);
	path++;
	path++;
	path++;
	path++;
	path++;

	loop(env, my_env);	
	exit (EXIT_SUCCESS);
}