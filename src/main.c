/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:32:04 by asimone           #+#    #+#             */
/*   Updated: 2023/11/23 14:29:36 by pskrucha         ###   ########.fr       */
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
	char	*line;

	while (1)
	{
	line = readline(GREEN BOLD "mustash> "RESET);
	args = ft_split(line, ' ');
	add_history(line);
	//rl_on_new_line();
		if (!ft_strncmp("ls", *args, 3))
		{
			if (g_signal == 1)
				my_env->exit_status = 130;
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		add_history(line);
		if (g_signal)
		{
			my_env->exit_status = TERMINATION_SIGINT;
			g_signal = 0;
		}
		if (ft_strlen(line) > 0)
			lexer(line, my_env);
		ft_free(line);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **env)
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
		
		loop();	
	}
	exit (EXIT_SUCCESS);
}
