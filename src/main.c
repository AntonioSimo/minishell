/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:52:43 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_code;

void	loop(t_env *my_env)
{
	char	*line;

	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		add_history(line);
		if (ft_strlen(line) > 0)
			lexer(line, my_env);
		ft_free(line);
		rl_on_new_line();
	}
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*env_main;

// 	(void)argv;
// 	(void)argc;
// 	g_error_code = 0;
// 	env_main = NULL;
// 	copy_env(env, &env_main);
// 	signal(SIGINT, signal_int_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	loop(env_main);
// 	exit (EXIT_SUCCESS);
// }

int main(int argc, char **argv, char **env) 
{
	(void) argv;
	(void) argc;
    t_env *env_main = malloc(sizeof(t_env)); // Alloca memoria per la struct t_env
    if (env_main == NULL) {
        // Gestione dell'errore se la memoria non può essere allocata
        fprintf(stderr, "Errore: memoria non allocata per env_main\n");
        exit(EXIT_FAILURE);
    }

    env_main->exit_status = 0;
    env_main->env = NULL; // Assicurati di inizializzare gli altri membri della struct come necessario
    env_main->env_copy = NULL;

    //env_main = copy_env(env, &env_main); // Assegna il puntatore alla struttura t_env
	copy_env(env, &env_main);
    signal(SIGINT, signal_int_handler);
    signal(SIGQUIT, SIG_IGN);
    loop(env_main);
    //free_env(env_main); // Assicurati di liberare la memoria quando non ne hai più bisogno
    free(env_main); // Libera la memoria allocata per la struttura t_env
    exit(EXIT_SUCCESS);
}

