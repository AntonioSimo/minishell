/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/23 14:49:35 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	if_not_space(t_token *tokens)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (tokens)
	{
		if (tokens->type == SEPERATOR)
			flag = true;
		i++;
		tokens = tokens->next;
	}
	if (flag && i == 1)
		return (1);
	return (0);
}

int	parse_line(char *line, t_env *env)
{
	t_command	*commands;
	t_token		*tokens;
	bool		flag;

	flag = true;
	tokens = tokenize(line);
	expander(&tokens, env);
	if (tokens && !if_not_space(tokens) && !check_pipes(tokens, env))
	{
		commands = merge_tokens(tokens, env);
		if (commands)
		{
			flag = false;
			run_commands(commands, env);
		}
		commands = destroy_cmds(commands);
	}
	tokens = destroy_tokens(tokens);
	if (flag)
		return (1);
	return (0);
}

int	lexer(char *line, t_env *my_env)
{
	if (check_quotes(line))
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
