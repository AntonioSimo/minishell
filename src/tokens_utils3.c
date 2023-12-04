/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:46:44 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/04 13:40:51 by asimone          ###   ########.fr       */
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

static void	append_tokens(t_token **tokens, char *line)
{
	int		i;
	t_type	quotes;

	i = 0;
	while (line[i])
	{
		quotes = quotes_type(line, i);
		if (quotes == SINGLE_QUOTED || quotes == DOUBLE_QUOTED)
			tokenize_quotted(tokens, line, &i, quotes);
		if (quotes == DEFAULT)
		{
			if (ft_isspace(line[i]))
				tokenize_space(tokens, line, &i);
			else
			{
				if (ft_strchr("|<>", line[i]))
					tokenize_symbols(tokens, line, &i);
				else
					tokenize_word(tokens, line, &i);
			}
		}
	}
}

int	check_and_append(char *extra_line, t_token **tokens, t_env *env, \
					char **line)
{
	if (check_quotes(extra_line))
	{
		append_tokens(tokens, extra_line);
		expander(tokens, env);
		*line = ptr_check(ft_free_strjoin(*line, extra_line));
		free(extra_line);
		return (0);
	}
	else
		ft_putstr_fd("mustash: syntax error: unexpected end of file\n", \
			STDERR_FILENO);
	return (1);
}
