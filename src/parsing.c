/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 17:54:45 by pskrucha         ###   ########.fr       */
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

int	handle_redirections(t_redir **redir, t_token **tokens)
{
	t_type	redir_type;
	char	*file;
	int		i;

	i = 0;
	file = NULL;
	if (!*redir)
	{
		(*redir) = ptr_check(malloc(sizeof(t_redir)));
		(*redir)->lst = NULL;
		(*redir)->stdin_cpy = dup(STDIN_FILENO);
		(*redir)->stdout_cpy = dup(STDOUT_FILENO);
	}
	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == SEPERATOR)
		*tokens = (*tokens)->next;
	while (*tokens)
	{
		if ((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED
			|| (*tokens)->type == SINGLE_QUOTED)
		{
			file = ft_free_strjoin(file, (*tokens)->command);
		}
		else if ((*tokens)->type == SEPERATOR || (*tokens)->type == PIPE || (*tokens)->type == REDIR_INPUT
			|| (*tokens)->type == REDIR_OUTPUT_APPEND || (*tokens)->type == HEREDOC
			|| (*tokens)->type == REDIR_OUTPUT)
		{
			if (!(redir_type == REDIR_OUTPUT && (*tokens)->type == PIPE && i == 0))
			{
				break ;
			}
		}
		i++;
		*tokens = (*tokens)->next;
	}
	if (!file)
	{
		ft_putstr_fd("Redirection error\n", STDERR_FILENO);
		return (1);
	}
	push_redir(&(*redir)->lst, lst_redir_new(file, redir_type));
	return (0);
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

int	check_if_redir(t_type type)
{
	if (type == DEFAULT || type == SEPERATOR
		|| type == PIPE)
		return (0);
	return (1);
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
		{
			if (handle_redirections(&redir, &tokens))
				return (NULL);
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
		free(var->word);
		redir = NULL;
	}
	return (commands);
}
