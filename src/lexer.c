/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/08/16 20:07:55 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_error_code;

void	skip_quotes(char *line, int *i, t_type *quotes)
{
	int	quotted_len;

	quotted_len = strlen_quoted(line, *i, *quotes);
	ft_printf("quoted len: %i \n", quotted_len);
	*i += quotted_len + 2;
	*quotes = DEFAULT;
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

void	lexer(char *line, t_envepval *my_env)
{
	bool quotes;
	t_token	*tokens;

	tokens = NULL;	
	quotes = check_quotes(line);
	if (quotes)
	{
		//scanner(line);
		tokenize(line, &tokens);
		//combine_tokens(tokens);
		//check_pipes(tokens);
		expander(tokens, my_env);
		
		//printf("error code: %i\n", g_error_code);
		print_list(tokens);
		destroy_tokens(tokens);
	}	
	else
		ft_printf("Unclosed quotes.\n");
}

