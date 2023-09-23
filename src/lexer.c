/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/21 22:11:23 by pskrucha         ###   ########.fr       */
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
		|| type == DOUBLE_QUOTED)
		return (1);
	return (0);
}

char	**get_command(char **args)
{
	char	**new_args;
	char	**first_row;
	int 	i;

	i = 0;
	if (!args)
		return (NULL);
	first_row = ptr_check(ft_split(args[0], ' '));
	new_args = NULL;
	if (first_row)
	{
		while (first_row[i])
		{
			new_args = push_str_2d(new_args, first_row[i]);
			i++;
		}
		i = 1;
	}
	while (args[i])
	{
		new_args = push_str_2d(new_args, args[i]);
		i++;
	}
	while (i >= 0)
	{
		free(args[i]);
		i--;
	}
	free(args);
	return (new_args);
}

void	handle_redirections(t_redir **redir, t_token *tokens)
{
		t_type	redir_type;
		char	*file;

		redir_type = tokens->type;
		while (tokens)
		{
			if (tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED
				|| tokens->type == SINGLE_QUOTED)
				{
					file = ptr_check(ft_strdup(tokens->command));
					push_redir(redir, lst_redir_new(file, redir_type));
					break ;
				}
			*tokens = *(tokens)->next;
		}
}

t_command	*merge_tokens(t_token	*tokens)
{
 	t_command	*commands;
	char		*word;
	char		**args_arr;
	t_redir		*redir;

	commands = NULL;
	args_arr = NULL;
	redir = NULL;
	word = NULL;
	while (tokens)
	{
		if (tokens->type == REDIR_INPUT || tokens->type == REDIR_OUTPUT
			|| tokens->type == REDIR_OUTPUT_APPEND || tokens->type == HEREDOC)
				handle_redirections(&redir, tokens);
		else if (is_word(tokens->type))
		{
			word = ft_free_strjoin(word, tokens->command);
		}
		else if (tokens->type == SEPERATOR)
		{
			args_arr = push_str_2d(args_arr, word);
			word = ft_free(word);
		}
		else if (tokens->type == PIPE)
		{
			args_arr = push_str_2d(args_arr, word);
			// args_arr = get_command(args_arr);
			push_cmd(&commands, lst_cmd_new(args_arr, redir));
			redir = NULL;
			word = ft_free(word);
			args_arr = NULL;
		}
		
		tokens = tokens->next;
	}
	if (word || args_arr)
	{
		args_arr = push_str_2d(args_arr, word);
		// args_arr = get_command(args_arr);
		if (args_arr)
			push_cmd(&commands, lst_cmd_new(args_arr, redir));
		word = ft_free(word);
		redir = NULL;
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
					ft_printf("i: %i\n", i);
					i++;
				}
				else
					i++;
			}
		}
	}
}

// void	check_redirections(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		if (tokens->type == )
// 	}
	
// }

void	lexer(char *line, t_env *my_env, char *or_home)
{
	t_token		*tokens;
	// t_command	*commands;
	
	tokens = NULL;	
	if (check_quotes(line))
	{
		
		//scanner(line);
		tokenize(line, &tokens);
		expander(tokens, my_env->env, or_home);
		// check_redirections(tokens);
		print_tokens(tokens);
		// commands = merge_tokens(tokens);
		// parse_redirections(commands);
		//printf("error code: %i\n", g_error_code);
	
		// print_cmds(commands);
		// run_commands(commands, my_env);	
		destroy_tokens(tokens);
		// commands = destroy_cmds(commands);
	}	
	else
		ft_printf("Unclosed quotes.\n");
}

