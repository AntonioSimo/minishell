/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:44 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/23 16:26:52 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	attach_empty_head(pos, head, or_head);
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
	attach_head(pos, head, or_head);
}

t_token	*create_new_nodes(char *expanded, t_type type)
{
	char	**temp_arr;
	t_token	*new_nodes;
	int		i;
	char	*token;

	i = 0;
	new_nodes = NULL;
	if (ft_strlen(expanded) == 0)
	{
		push_token(&new_nodes, lst_token_new("", type));
		return (new_nodes);
	}
	temp_arr = ptr_check(ft_split(expanded, ' '));
	while (temp_arr[i])
	{
		token = ptr_check(ft_strdup(temp_arr[i]));
		push_token(&new_nodes, lst_token_new(token, type));
		if (temp_arr[i + 1])
			push_token(&new_nodes, lst_token_new(" ", SEPERATOR));
		free(token);
		i++;
	}
	temp_arr = double_free(temp_arr);
	return (new_nodes);
}
