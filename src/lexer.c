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

// t_command	*merge_tokens(t_token	*tokens)
// {
// 	t_command	*commands;

// }

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
	// t_command	*commands;

	tokens = NULL;	
	if (check_quotes(line))
	{
		//scanner(line);
		tokenize(line, &tokens);
		//combine_tokens(tokens);
		//check_pipes(tokens);
		expander(tokens, my_env, or_home);
		// commands = merge_tokens(tokens);
		//printf("error code: %i\n", g_error_code);
		print_tokens(tokens);
		destroy_tokens(tokens);
	}	
	else
		ft_printf("Unclosed quotes.\n");
}

