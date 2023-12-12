/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 18:27:57 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	scann_for_pipes(t_token *tokens, int *flag, t_env *env)
{
	while (tokens)
	{
		if (!not_pipe(tokens->type))
			*flag = 0;
		if (*flag && tokens->type == PIPE)
		{
			ft_putstr_fd("Incorrect pipes\n", STDERR_FILENO);
			env->exit_status = 2;
			return (1);
		}
		if (tokens->type == PIPE)
			*flag = 1;
		tokens = tokens->next;
	}
	return (0);
}

int	check_pipes(t_token **tokens, t_env *env, char **line)
{
	int		flag;
	t_token	*head;
	int		ctrl_c;

	ctrl_c = 0;
	flag = 1;
	head = *tokens;
	if (scann_for_pipes(*tokens, &flag, env))
		return (1);
	*tokens = head;
	if (!flag)
		return (0);
	if (cat_line(tokens, env, line, &ctrl_c))
	{
		if (ctrl_c)
			return (1);
		destroy_tokens(*tokens);
		free(*line);
		exit (free_env(env));
	}
	if (check_pipes(tokens, env, line))
		return (1);
	return (0);
}

int	parse_line(char **line, t_env *env)
{
	t_command	*commands;
	t_token		*tokens;
	bool		flag;

	flag = true;
	tokens = tokenize(*line);
	expander(&tokens, env);
	if (tokens && !if_not_space(tokens) && !check_pipes(&tokens, env, line))
	{
		if (tokens)
		{
			commands = merge_tokens(tokens, env);
			print_cmds(commands);
			if (commands && !run_commands(commands, env))
				flag = false;
			commands = destroy_cmds(commands);
		}
		else
			return (1);
	}
	tokens = destroy_tokens(tokens);
	if (flag)
		return (1);
	return (0);
}

int	lexer(char **line, t_env *my_env)
{
	if (check_quotes(*line))
	{
		if (!parse_line(line, my_env))
			return (0);
	}
	else
	{
		ft_putstr_fd("mustash: syntax error: unexpected end of file\n", \
		STDERR_FILENO);
		my_env->exit_status = SYNTAX_ERROR;
	}
	return (1);
}
