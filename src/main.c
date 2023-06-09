/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 14:32:04 by asimone       #+#    #+#                 */
/*   Updated: 2023/06/07 22:32:07 by asimone       ########   odam.nl         */
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

#include <unistd.h>
#include <stdio.h>

int main() {
    char *binaryPath = "/bin/echo";
    char *args[] = {"echo", "Hello, additional message!", NULL};
    char *env[] = {NULL};

    execve(binaryPath, args, env);

    // execve will only return if an error occurs
    perror("execve");
    return 1;
}
