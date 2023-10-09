/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/08/16 15:57:33 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct s_parsing
{
	char	*word;
	char	**args_arr;
}	t_parsing;

t_parsing	*set_parsing_var(void)
{
	t_parsing	*var;

	var = ptr_check(malloc(sizeof(t_parsing)));
	var->args_arr = NULL;
	var->word = NULL;
	return (var);
}

void	handle_redirections(t_redir **redir, t_token *tokens)
{
	t_type	redir_type;
	char	*file;

	if (!*redir)
	{
		(*redir) = ptr_check(malloc(sizeof(t_redir)));
		(*redir)->lst = NULL;
		(*redir)->stdin_cpy = dup(STDIN_FILENO);
		(*redir)->stdout_cpy = dup(STDOUT_FILENO);
	}
	redir_type = tokens->type;
	while (tokens)
	{
		if (tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED
			|| tokens->type == SINGLE_QUOTED)
		{
			file = ptr_check(ft_strdup(tokens->command));
			push_redir(&(*redir)->lst, lst_redir_new(file, redir_type));
			break ;
		}
		*tokens = *(tokens)->next;
	}
}

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

t_command	*merge_tokens(t_token	*tokens)
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
			handle_redirections(&redir, tokens);
		else
			handle_cmds(tokens, &commands, &redir, &var);
		tokens = tokens->next;
	}
	if (var->word || var->args_arr || redir)
	{
		var->args_arr = push_str_2d(var->args_arr, var->word);
		if (var->args_arr || redir)
			push_cmd(&commands, lst_cmd_new(var->args_arr, redir));
		free(var->word);
		redir = NULL;
	}
	return (commands);
}
