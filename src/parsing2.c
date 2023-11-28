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

int	if_not_redir(t_type type)
{
	if (type == DEFAULT || type == SEPERATOR
		|| type == PIPE || type == SINGLE_QUOTED
		|| type == DOUBLE_QUOTED)
		return (0);
	return (1);
}

int	free_parsing_temp(t_parsing *temp, int check)
{
	if (check)
	{
		if (temp->args_arr)
			double_free(temp->args_arr);
	}
	if (temp->word)
		free(temp->word);
	free(temp);
	return (0);
}

int	if_redir(t_type type)
{
	if (type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND || type == HEREDOC)
		return (0);
	return (1);
}

void	handle_leftover(t_parsing *var, t_redir *redir, t_command **commands)
{
	var->args_arr = push_str_2d(var->args_arr, var->word);
	if (var->args_arr || redir)
		push_cmd(commands, lst_cmd_new(var->args_arr, redir));
	free_parsing_temp(var, 0);
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
		if (!if_redir(tokens->type))
		{
			if (handle_redirections(&redir, &tokens, env)
				&& free_parsing_temp(var, 1))
				return (NULL);
		}
		if (!tokens)
			break ;
		handle_cmds(tokens, &commands, &redir, &var);
		if (!if_not_redir(tokens->type))
			tokens = tokens->next;
	}
	if (var->word || var->args_arr || redir)
		handle_leftover(var, redir, &commands);
	return (commands);
}
