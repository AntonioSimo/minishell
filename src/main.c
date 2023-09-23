/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:14 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/21 16:55:37 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_error_code;

void	loop(t_env *my_env)
{
	char *line;
	char *or_home;

	or_home = ptr_check(find_expandable(my_env->env, "HOME"));
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
			lexer(line, my_env, or_home);
		ft_free(line);
		rl_on_new_line();
	}
}	

void nic(t_token **token, t_token *temp)
{
	t_token	*head;
	// t_token	*new_lst;

	head = *token;
	*token = (*(token))->next;
	*token = (*(token))->next;
	// (void)temp;
	// token->next->command = ft_strdup("hihi");
	connect_nodes(temp, token, 2, &head);

	*token = head;
	// destroy_tokens(*token);
	printf("segf\n");
	// print_tokens(*token);
	
}

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_env   *env_main;
	t_token	*token;
	t_token	*temp;
	(void)env_main;

	token = NULL;
	
	g_error_code = 0;
	env_main = copy_env(env);
	// signal(SIGINT, signal_int_handler);
	// signal(SIGQUIT, SIG_IGN);
	push_token(&token, lst_token_new("1", DEFAULT));
	push_token(&token, lst_token_new("2", DEFAULT));
	push_token(&token, lst_token_new("3", DEFAULT));
	push_token(&token, lst_token_new("5", DEFAULT));
	push_token(&token, lst_token_new("6", DEFAULT));
	push_token(&token, lst_token_new("7", DEFAULT));
	push_token(&temp, lst_token_new("a", DEFAULT));
	push_token(&temp, lst_token_new("b", DEFAULT));
	
	// temp = create_nodes("", "12a", 1, 1);
	print_tokens(token);
	printf("siala\n");
	nic(&token, temp);
	printf("in main\n");
	print_tokens(token);


	// loop(env_main);	
	exit (EXIT_SUCCESS);
}
