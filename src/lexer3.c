/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/28 17:30:59 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_divider(t_type type)
{
	if (type == PIPE || type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	if_not_space(t_token *tokens)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (tokens)
	{
		if (tokens->type == SEPERATOR)
			flag = true;
		i++;
		tokens = tokens->next;
	}
	if (flag && i == 1)
		return (1);
	return (0);
}
