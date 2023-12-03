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

void	get_input_child(int fd[2])
{
	char	*extra_line;

	close(fd[0]);
	while (1)
	{
		extra_line = readline(">");
		if (!extra_line)
		{
			close(fd[1]);
			exit(1);
		}
		if (ft_strlen(extra_line) > 0)
		{
			ft_putstr_fd(extra_line, fd[1]);
			close(fd[1]);
			exit(0);
		}
		free(extra_line);
	}
}

int	wait_for_line(int pid, t_env *env)
{
	int	status;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (0);
		else
		{
			ft_putstr_fd("mustash: syntax error: unexpected end of file\n", \
			STDERR_FILENO);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			env->exit_status = SYNTAX_ERROR;
			return (1);
		}
	}
	env->exit_status = 130;
	return (0);
}

char *process_extra_line(int *fd)
{
	char 	*line;
	line = get_next_line(fd[0]);
	if (!line)
		return (NULL);
	close(fd[0]);
	return (line);
}

int	cat_line(t_token **tokens, t_env *env, char **line, int *ctrl_c)
{
	int		fd[2];
	int		pid;
	char	*extra_line;

	rl_on_new_line();
	if (pipe(fd) == -1)
		perror_exit("Pipe creation failed\n");
	pid = fork();
	if (pid == -1)
		perror_exit("Fork error\n");
	manage_signals(0);
	if (pid == 0)
	{
		manage_signals(2);
		get_input_child(fd);
	}
	if (wait_for_line(pid, env))
		return (1);
	close(fd[1]);
	extra_line = process_extra_line(fd);
	manage_signals(1);
	if (!extra_line)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		*ctrl_c = 1;
		return (1);
	}
	check_and_append(extra_line, tokens, env, line);
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
