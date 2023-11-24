/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:44 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/23 16:26:52 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_lst_size(t_token	*tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

t_token	*create_token(char *string, t_type type)
{
	t_token	*token;

	token = ptr_check(malloc(sizeof(t_token)));
	token->command = ptr_check(ft_strdup(string));
	token->type = type;
	return (token);
}

void	attach_empty_head(int pos, t_token **head, t_token *or_head)
{
	t_token	*temp;

	if (pos == 0)
	{
		temp = (*head)->next;
		free((*head)->command);
		free(*head);
		*head = temp;
	}
	else
	{
		temp = (*head)->next;
		free((*head)->command);
		free(*head);
		*head = or_head;
	}
}

void	attach_head(int pos, t_token **head, t_token *or_head)
{
	t_token	*temp;

	if (pos == 0)
	{
		temp = (*head)->next;
		free((*head)->command);
		free(*head);
		*head = temp;
	}
	else
	{
		free((*head)->command);
		free(*head);
		*head = or_head;
	}
}
