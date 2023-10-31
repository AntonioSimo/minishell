/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/26 18:24:37 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_error_code;

int	is_divider(t_type type)
{
	if (type == PIPE || type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	check_pipes(t_token *tokens, t_env *env)
{
	bool	flag;

	flag = true;
	while (tokens)
	{
		if (tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED
			|| tokens->type == SINGLE_QUOTED || tokens->type == REDIR_INPUT
			|| tokens->type == REDIR_OUTPUT
			|| tokens->type == REDIR_OUTPUT_APPEND
			|| tokens->type == HEREDOC)
			flag = false;
		if (flag && tokens->type == PIPE)
		{
			ft_putstr_fd("Incorrect pipes\n", STDERR_FILENO);
			env->exit_status = 2;
			return (1);
		}
		if (tokens->type == PIPE)
			flag = true;
		tokens = tokens->next;
	}
	if (!flag)  
		return (0);
	ft_putstr_fd("Incorrect pipes\n", STDERR_FILENO);	
	return (1); 
}

void	lexer(char *line, t_env *my_env)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = NULL;
	if (check_quotes(line))
	{
		tokenize(line, &tokens);
		expander(&tokens, my_env);
		if (tokens && !check_pipes(tokens, my_env))
		{
			commands = merge_tokens(tokens, my_env);
			// if (check_assignments(commands))
			// 	remove_assigmnets(&commands);
			if (commands)
				run_commands(commands, my_env);
			tokens = destroy_tokens(tokens);
			commands = destroy_cmds(commands);
		}
	}
	else
	{
		ft_putstr_fd("mustash: syntax error: unexpected end of file\n", STDERR_FILENO);
		my_env->exit_status = SYNTAX_ERROR;
	}
}
