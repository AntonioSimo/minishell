/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:00:23 by pskrucha         ###   ########.fr       */
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

int	check_pipes(t_token *tokens)
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
		if (flag && tokens->type == PIPE && printf("Incorrect pipes\n"))
			return (1);
		if (tokens->type == PIPE)
			flag = true;
		tokens = tokens->next;
	}
	if (flag && printf("Incorrect pipes\n"))
		return (1);
	return (0);
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
		if (tokens && !check_pipes(tokens))
		{
			// print_tokens(tokens);
			commands = merge_tokens(tokens);
			// print_cmds(commands);
			if (commands)
				run_commands(commands, my_env);
			destroy_tokens(tokens);
		}
	}
	else
	{
		printf("mustash: syntax error: unexpected end of file\n");
		my_env->exit_status = SYNTAX_ERROR;
	}
}
