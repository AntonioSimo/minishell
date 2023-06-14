/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:32:04 by asimone           #+#    #+#             */
/*   Updated: 2023/06/14 15:27:08 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int j;
	//printf("here \n");

	i = 0;
	j = 6;
	while (env[i])
	{
		//printf("line: %s\n", env[i]);
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			while (--j)
				env[i]++;
			return (env[i]);
		}
		i++;
	}
	return ("NIC");
	
}

void	execute_command(char **single_path, char **env)
{
	char* arr[] = {"/ls", "-la", NULL};
	int i;
	char *path_with_command;

	
	//(void)env;
	i = 0;
	while (single_path[i])
	{
		path_with_command = ft_free_strjoin(single_path[i], arr[0]);
		if (!path_with_command)
			exit(EXIT_FAILURE);
		printf("path with command: >>%s<<\n", path_with_command);
		//printf("path: >>%s<<\n", single_path[i]);
		execve(path_with_command, arr, env);
		i++;
		free(path_with_command);
		path_with_command = NULL;
	}
	printf("command not found\n");
	exit(EXIT_FAILURE);
}

void	loop(char **env)
{
	char *line;
	char **args;
	pid_t	pid;
	int  status;
	char pwd[FILENAME_MAX + 1];
	char *path;
	char **single_path;

	path = get_path(env);
	printf("path: %s", path);
	
	while (1)
	{
	line = readline(GREEN BOLD "mustash> "RESET);
	args = ft_split(line, ' ');
	add_history(line);
	//rl_on_new_line();
		if (!ft_strncmp("ls", *args, 3))
		{
			single_path = ft_split(path, ':');
			if (!single_path)
				exit(EXIT_FAILURE);
			pid = fork();
			if (pid == 0)
			{
				execute_command(single_path, env);
			}
			waitpid(pid, &status, 0);
		}
		if (!ft_strncmp("pwd", *args, 4))
		{
			printf("%s\n", getcwd(pwd, sizeof(pwd)));
		}
		if (!ft_strncmp("cd", args[0], 3))
		{
			if (chdir(args[1]))
				printf("no such file or directory\n");
		}
		else if (!ft_strncmp("exit", *args, 5))
			exit(EXIT_SUCCESS);
	}
	free(line);
	free(args);
}	

int	main(int argc, char** argv, char** env)
{
	//int i = 0;
	(void) argv;
	(void) argc;
	//char pwd[100];

	//printf("path: %s\n", getcwd(pwd, 100));
	//printf("path: %s\n", getcwd(pwd, 100));
	
	//char *trimmed_path = ft_strtrim(path, "")
	
	//if (argc >= 0)
	//{
	//	while (envep[i])
	//	{
	//		printf("%s\n", envep[i]);
	//		i++;
	//	}
	while (1)
	{
		
		loop(env);	
	}
	exit (EXIT_SUCCESS);
}