/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:44 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:51:42 by pskrucha         ###   ########.fr       */
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

static int	empty_node(int pos, t_token **head)
{
	int		i;
	t_token	*or_head;
	t_token	*next_head;
	t_token	*prev_to_append;

	i = 0;
	or_head = *head;
	prev_to_append = *head;
	while (i < pos)
	{
		*head = (*(head))->next;
		if (i == pos - 2)
			prev_to_append = *head;
		i++;
	}
	next_head = (*head)->next;
	prev_to_append->next = next_head;
	if (pos == 0)
		*head = or_head->next;
	else
		*head = or_head;
	return (1);
}

void	connect_nodes(t_token *new_nodes, int pos, t_token **head)
{
	int		i;
	t_token	*or_head;
	t_token	*next_head;
	t_token	*prev_to_append;

	i = 0;
	or_head = *head;
	prev_to_append = *head;
	if (!new_nodes && empty_node(pos, head))
		return ;
	while (i++ < pos)
	{
		*head = (*(head))->next;
		if (i == pos - 1)
			prev_to_append = *head;
	}
	next_head = (*head)->next;
	prev_to_append->next = new_nodes;
	while (new_nodes->next)
		new_nodes = new_nodes->next;
	new_nodes->next = next_head;
	if (pos == 0)
		*head = or_head->next;
	else
		*head = or_head;
}