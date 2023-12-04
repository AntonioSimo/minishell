/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/04 13:36:15 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parsing	*set_parsing_var(void)
{
	t_parsing	*var;

	var = ptr_check(malloc(sizeof(t_parsing)));
	var->args_arr = NULL;
	var->word = NULL;
	return (var);
}

void	handle_cmds(t_token *tokens, t_command **commands, \
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
