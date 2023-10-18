/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 18:39:23 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_signal;

void	minishell(t_env *my_env)
{
	char	*line;

	while (1)
	{
		manage_signals(1);
		line = readline(GREEN BOLD "mustash> "RESET);
		// manage_signals(0);
		if (!line)
		{
			if (g_signal == 1)
				my_env->exit_status = 130;
			printf("exit\n");
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
		if (g_signal)
			printf("\n");
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env   *env_main;

	(void)argv;
	(void)argc;
	env_main = NULL;
	g_signal = 0;
	manage_signals(0);
	copy_env(env, &env_main);
	minishell(env_main);
	exit (env_main->exit_status);
}



// int main() {
// 	g_signal = 0;
// 	(void)g_signal;
// 	// char *line;
// 	manage_signals(1);
//     int **a = malloc(sizeof(int*) * 4);
//     a[0] = malloc(sizeof(int) * 2);
//     a[1] = malloc(sizeof(int) * 2);
//     a[2] = malloc(sizeof(int) * 2);
//     a[3] = malloc(sizeof(int) * 2);
//     pid_t pid, pid2, pid3, pid4, pid5;
//     int status;
//     if (pipe(a[0]) == -1) {
//         perror("Pipe creation failed");
//         exit(1);
//     }
//     pid = fork();
//     if (pid == 0) {
//         close(a[0][0]);
//         dup2(a[0][1], STDOUT_FILENO);
//         close(a[0][1]);
//         execlp("cat",  "cat", NULL);
//         perror("exec");
//         exit(1);
//     }
//     close(a[0][1]);
//     // close(a[0]);
//     if (pipe(a[1]) == -1) {
//         perror("Pipe creation failed");
//         exit(1);
//     }
//     pid2 = fork();
//     if (pid2 == 0) {
//         close(a[1][0]);
//         dup2(a[0][0], STDIN_FILENO);
//         dup2(a[1][1], STDOUT_FILENO);
//         close(a[0][0]);
//         close(a[1][1]);
//         execlp("cat",  "cat", NULL);
//         // execlp("cat",  "cat", NULL);
//         perror("exec");
//         exit(1);
//     }
//     close(a[0][0]);
//     close(a[1][1]);
//     if (pipe(a[2]) == -1) {
//         perror("Pipe creation failed");
//         exit(1);
//     }
//     pid3 = fork();
//     if (pid3 == 0) {
//         close(a[2][0]);
//         dup2(a[1][0], STDIN_FILENO);
//         dup2(a[2][1], STDOUT_FILENO);
//         close(a[1][0]);
//         close(a[2][1]);
//  	    execlp("echo",  "echo", "j", NULL);
//         perror("exec");
//         exit(1);
//     }
//     close(a[1][0]);
//     close(a[2][1]);
//     if (pipe(a[3]) == -1) {
//         perror("Pipe creation failed");
//         exit(1);
//     }
//     pid4 = fork();
//     if (pid4 == 0) {
//         close(a[3][0]);
//         dup2(a[2][0], STDIN_FILENO);
//         dup2(a[3][1], STDOUT_FILENO);
//         close(a[2][0]);
//         close(a[3][1]);
//         execlp("cat",  "cat", NULL);
//         perror("exec");
//         exit(1);
//     }
//     close(a[2][0]);
//     close(a[3][1]);
//     pid5 = fork();
// if (pid5 == 0) {
//     dup2(a[3][0], STDIN_FILENO);
//     close(a[3][0]);
//     // execlp("ls", "ls", NULL);
//     execlp("echo",  "echo", "j", NULL);
//     perror("exec");
//     exit(1);
// }
//     close(a[3][0]);
//     waitpid(pid, &status, 0);
//     waitpid(pid2, &status, 0);
//     waitpid(pid3, &status, 0);
//     waitpid(pid4, &status, 0);
//     waitpid(pid5, &status, 0);
//     return 0;
// }