/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 17:30:59 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	append_tokens(t_token **tokens, char *line)
{
	int		i;
	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
			tokenize_quotted(tokens, line, &i, quotes);
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
				tokenize_space(tokens, line, &i);
			else
			{
				if (ft_strchr("|<>", line[i]))
					tokenize_symbols(tokens, line, &i);
				else
					tokenize_word(tokens, line, &i);
			}
		}
	}
}

static int	check_and_append(char *extra_line, t_token **tokens, t_env *env, \
					char **line)
{
	if (check_quotes(extra_line))
	{
		append_tokens(tokens, extra_line);
		expander(tokens, env);
		*line = ft_free_strjoin(*line, extra_line);
		return (0);
	}
	else
		ft_putstr_fd("mustash: syntax error: unexpected end of file\n", \
			STDERR_FILENO);
	return (1);
}

int	cat_line(t_token **tokens, t_env *env, char **line) //here should be child process i think to exit from input by pressing ctrl + c
{
	char	*extra_line;

	rl_on_new_line();
	while (1)
	{
		extra_line = readline(">");
		if (!extra_line)
		{
			if (g_signal == 1)
				env->exit_status = 130;
			ft_putstr_fd("exit\n", STDERR_FILENO);
			return (1);
		}
		if (ft_strlen(extra_line) > 0)
		{
			if (!check_and_append(extra_line, tokens, env, line))
				break ;
		}
		free(extra_line);
	}
	free(extra_line);
	return (0);
}

int	is_divider(t_type type)
{
	if (type == PIPE || type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	not_pipe(t_type type)
{
	if (type == DEFAULT || type == DOUBLE_QUOTED
		|| type == SINGLE_QUOTED || type == REDIR_INPUT
		|| type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND
		|| type == HEREDOC)
		return (0);
	return (1);
}
