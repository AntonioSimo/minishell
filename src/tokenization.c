/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:49:20 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 18:30:11 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize_space(t_token **token_lst, char *line, int *i)
{
	push_token(token_lst, lst_token_new(" ", SEPERATOR));
	while (ft_isspace(line[*i]))
		*i += 1;
}

void	tokenize_symbols(t_token **token_lst, char *line, int *i)
{
	if (line[*i] == '|')
		tokenize_pipe(token_lst, i);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		tokenize_heredoc(token_lst, i);
	else if (line[*i] == '<')
		tokenize_redir_in(token_lst, i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		tokenize_redir_outapp(token_lst, i);
	else if (line[*i] == '>')
		tokenize_redir_out(token_lst, i);
}

void	tokenize_word(t_token **token_lst, char *line, int *position)
{
	char	*word;
	int		i;

	i = 0;
	while (line[*position + i] && !ft_strchr("|<>\'\"", line[*position + i]) \
			&& !ft_isspace(line[*position + i]))
		i++;
	word = ft_substr(line, *position, i);
	*position += i;
	push_token(token_lst, lst_token_new(word, DEFAULT));
	free(word);
}

void	tokenize_quotted(t_token **token_lst, char *line, int *pos, \
						t_type quotes)
{
	int		quotes_len;
	char	*quotted_sentence;

	quotes_len = strlen_quoted(line, *pos, quotes);
	quotted_sentence = ptr_check(ft_substr(line, *pos + 1, quotes_len));
	push_token(token_lst, lst_token_new(quotted_sentence, quotes));
	free(quotted_sentence);
	*pos += quotes_len + 2;
}

void	tokenize(char *line, t_token **token_lst)
{
	int		i;
	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
			tokenize_quotted(token_lst, line, &i, quotes);
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
				tokenize_space(token_lst, line, &i);
			else
			{
				if (ft_strchr("|<>", line[i]))
					tokenize_symbols(token_lst, line, &i);
				else
					tokenize_word(token_lst, line, &i);
			}
		}
	}
}
