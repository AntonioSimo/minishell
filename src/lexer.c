/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/06 13:32:28 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_error_code;

int	is_divider(t_type type)
{
	if (type == PIPE || type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_word(t_type type)
{
	if (type == DEFAULT || type == SINGLE_QUOTED
		|| type == DOUBLE_QUOTED || type == SEPERATOR)
		return (1);
	return (0);
}

 t_command	*merge_tokens(t_token	*tokens)
 {
 	t_command	*commands;
	char		*args;
	char		*temp;

	commands = NULL;
	args = NULL;
	temp = NULL;
	while (tokens)
	{
		if (is_word(tokens->type))
		{
			temp = ft_strjoin(args, tokens->command);
			ft_free(args);
			args = NULL;
			args = ft_strdup(temp);
			ft_free(temp);
			temp = NULL;

		}
		else if (is_divider(tokens->type))
		{
			push_cmd(&commands, lst_cmd_new(args));
			ft_free(args);
			args = NULL;
		}
		tokens = tokens->next;
	}
	if (args)
	{
		//printf("args here lol: %s \n",args);
		push_cmd(&commands, lst_cmd_new(args));
		ft_free(args);
	}
	return (commands);
 }

void	scanner(char *line)
{
	int i;
	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
			skip_quotes(line, &i, &quotes);
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
			{
				while (ft_isspace(line[i]))
					i += 1;
			}
			else
			
			{
				if (ft_strchr("|<>", line[i]))
				{
					//check_redirections(line, &i);
					ft_printf("i: %i\n", i);
					i++;
				}
				else
					i++;
			}
		}
	}
}

void	lexer(char *line, t_envepval *my_env, char *or_home)
{
	t_token		*tokens;
	 t_command	*commands;

	tokens = NULL;	
	if (check_quotes(line))
	{
		//scanner(line);
		tokenize(line, &tokens);
		//check_pipes(tokens);
		expander(tokens, my_env, or_home);
		commands = merge_tokens(tokens);
		//printf("error code: %i\n", g_error_code);
		print_tokens(tokens);
		print_cmds(commands);
		destroy_tokens(tokens);
		destroy_cmds(commands);
	}	
	else
		ft_printf("Unclosed quotes.\n");
}

