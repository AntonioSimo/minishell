#include "../include/minishell.h"

#define MUSTACHE "                                                   			   \n\
                        ████████░░      ██████████                ██               \n\
    ██                ██████████████  ██████████████░░            ░░██             \n\
 ██▒▒            ▒▒██████████████████████████████████▒▒            ████            \n\
 ██            ████████████████████████████████████████▒▒          ████            \n\
░██          ██████████████████████████████████████████████        ████            \n\
 ██▒▒    ▒▒██████████████████████████████████████████████████      ████            \n\
 ██████████████████████████████████████████████████████████████████████            \n\
 ██████████████████████████████████░░██████████████████████████████████            \n\
 ████████████████████████████████    ░░██████████████████████████████▒▒            \n\
 ░░████████████████████████████          ████████████████████████████              \n\
   ░░██████████████████████                ▒▒██████████████████████                \n\
       ████████████████                          ██████████████                    \n\
                                                                       \n"

//int main()
//{
//	char *str;
	
//	str = readline( GREEN BOLD "mustash> "RESET);
//	//printf("line = %s\n", str);
//	add_history(str);
//	printf("\n");
//	rl_on_new_line();
//	rl_replace_line("haha",0);
//	rl_redisplay();
//	free(str);
//    return 0;
//}

//int main()
//{
//    //char s[100];
 
//    //// printing current working directory
//    //printf("%s\n", getcwd(s, 100));
 
//    //// using the command
//    //chdir("../../..");
 
//    //// printing current working directory
//    //printf("%s\n", getcwd(s, 100));
//    // after chdir is executed
 

//	//char* arr[] = {NULL};
//	//execv("/Users/asimone/Desktop/Minishell/a.out", arr);
//	int fd = open("a.c", O_CREAT | O_RDONLY);
//	int fd2 = open("a.c", O_CREAT | O_RDONLY);
//	printf("fd before dup= %i\n", fd);
//	printf("fd2 before dup= %i\n", fd2);
//	int fd3 = dup(fd);
//	int fd4 = dup2(fd, 12);
//	printf("fd= %i\nfd2= %i\nfd3= %i\nfd4= %i\n", fd, fd2, fd3, fd4);
//    return 0;
//}

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

//void	execute_command(char **single_path, char **env)
//{
//	char *arr[] = {"ls", NULL, NULL};
//	int i;
//	char *path_with_command;
//	int fd;

//	i = 0;
//	while (single_path[i])
//	{
//		path_with_command = ft_free_strjoin(single_path[i], arr[0]);
//		printf("%s\n", path_with_command);
//		if (!path_with_command)
//			exit(EXIT_FAILURE);
//		fd = access(arr[0], F_OK | X_OK);
//		if (fd == 0)
//			execve(path_with_command, arr, env);
//		//printf("path with command: >>%s<<\n", path_with_command);
//		//printf("path: >>%s<<\n", single_path[i]);
//		i++;
//		free(path_with_command);
//		path_with_command = NULL;
//	}
//	if (fd == -1)
//		perror("command not found\n");
//	exit(EXIT_FAILURE);
//}

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

void	loop(char **env)
{
	char	*line;
	char	**args;
	char	*path;

	path = get_path(env);
	while (1)
	{
	line = readline(GREEN BOLD "mustash> "RESET);
	args = ft_split(line, ' ');
	add_history(line);
		if (!ft_strncmp("ls", *args, 3))
			execute_ls(env);
		if (!ft_strncmp("pwd", *args, 4))
			get_current_working_dir();
		if (!ft_strncmp("cd", *args, 3))
			execute_cd(*args);
		//if (!ft_strncmp("clear", *args, 6))
		//{
		//	clearScreen();
		//}
		else if (!ft_strncmp("exit", *args, 5))
			exit(EXIT_SUCCESS);
	}
	free(line);
	free(args);
}	


void	print_mustache()
{
write(1, MUSTACHE, sizeof MUSTACHE);         
}
int	main(int argc, char** argv, char** envep)
{
	//int i = 0;
	(void) argv;
	(void) argc;
	//char pwd[100];

	char *path = get_path(envep);

	path++;
	path++;
	path++;
	path++;
	path++;
	print_mustache();
//	printf("%s\n", *envep);
//	//printf("path: %s\n", getcwd(pwd, 100));
//	//printf("path: %s\n", getcwd(pwd, 100));
//int	main(int argc, char** argv, char** env)
//{
//	//int i = 0;
//	(void) argv;
//	(void) argc;
//	//char pwd[100];

//	//printf("path: %s\n", getcwd(pwd, 100));
//	//printf("path: %s\n", getcwd(pwd, 100));
	
////	//char *trimmed_path = ft_strtrim(path, "")
	
////	//if (argc >= 0)
////	//{
////	//	while (envep[i])
////	//	{
////	//		printf("%s\n", envep[i]);
////	//		i++;
////	//	}
////	while (1)
////	{
		
		loop(envep);	
////	}
	exit (EXIT_SUCCESS);
}
//		loop(env);	
//}
