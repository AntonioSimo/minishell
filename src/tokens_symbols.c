/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:39:18 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:09:40 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize_pipe(t_token **token_lst, int *i)
{
	push_token(token_lst, lst_token_new("|", PIPE));
	*i += 1;
}

void	tokenize_redir_in(t_token **token_lst, int *i)
{
	push_token(token_lst, lst_token_new("<", REDIR_INPUT));
	*i += 1;
}

void	tokenize_redir_out(t_token **token_lst, int *i)
{
	push_token(token_lst, lst_token_new(">", REDIR_OUTPUT));
	*i += 1;
}

void	tokenize_redir_outapp(t_token **token_lst, int *i)
{
	push_token(token_lst, lst_token_new(">>", REDIR_OUTPUT_APPEND));
	*i += 2;
}

void	tokenize_heredoc(t_token **token_lst, int *i)
{
	push_token(token_lst, lst_token_new("<<", HEREDOC));
	*i += 2;
}