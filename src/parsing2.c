/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/23 16:30:30 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cmds(t_token *tokens, t_command **commands, \
						t_redir **redir, t_parsing **var)
{
	if (is_word(tokens->type))
	{
		(*var)->word = ft_free_strjoin((*var)->word, tokens->command);
	}
	else if (tokens->type == SEPERATOR)
	{
		(*var)->args_arr = push_str_2d((*var)->args_arr, (*var)->word);
		(*var)->word = ft_free((*var)->word);
	}
	else if (tokens->type == PIPE)
	{
		(*var)->args_arr = push_str_2d((*var)->args_arr, (*var)->word);
		push_cmd(commands, lst_cmd_new((*var)->args_arr, *redir));
		*redir = NULL;
		(*var)->word = ft_free((*var)->word);
		(*var)->args_arr = NULL;
	}
}

int	check_if_redir(t_type type)
{
	if (type == DEFAULT || type == SEPERATOR
		|| type == PIPE || type == SINGLE_QUOTED
		|| type == DOUBLE_QUOTED)
		return (0);
	return (1);
}

void	free_parsing_temp(t_parsing *temp)
{
	// double_free(temp->args_arr);
	if (temp->word)
		free(temp->word);
	free(temp);
}

t_command	*merge_tokens(t_token	*tokens, t_env *env)
{
	t_command	*commands;
	t_redir		*redir;
	t_parsing	*var;

	var = set_parsing_var();
	commands = NULL;
	redir = NULL;
	while (tokens)
	{
		if (tokens->type == REDIR_INPUT || tokens->type == REDIR_OUTPUT
			|| tokens->type == REDIR_OUTPUT_APPEND || tokens->type == HEREDOC)
		{
			if (handle_redirections(&redir, &tokens, env))
			{
				if (var->args_arr)
					double_free(var->args_arr);
				free_parsing_temp(var);
				return (NULL);
			}
		}
		if (!tokens)
			break ;
		handle_cmds(tokens, &commands, &redir, &var);
		if (!check_if_redir(tokens->type))
			tokens = tokens->next;
	}
	if (var->word || var->args_arr || redir)
	{
		var->args_arr = push_str_2d(var->args_arr, var->word);
		if (var->args_arr || redir)
			push_cmd(&commands, lst_cmd_new(var->args_arr, redir));
	}
	free_parsing_temp(var);
	return (commands);
}
