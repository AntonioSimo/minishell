/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:57:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_error_code;

t_token	*create_new_nodes(char *expanded)
{
	char	**temp_arr;
	t_token	*new_nodes;
	int		i;
	char	*token;

	i = 0;
	new_nodes = NULL;
	if (ft_strlen(expanded) == 0)
	{
		push_token(&new_nodes, lst_token_new("", DEFAULT));
		return (new_nodes);
	}
	temp_arr = ptr_check(ft_split(expanded, ' '));
	while (temp_arr[i])
	{
		token = ptr_check(ft_strdup(temp_arr[i]));
		push_token(&new_nodes, lst_token_new(token, DEFAULT));
		if (temp_arr[i + 1])
			push_token(&new_nodes, lst_token_new(" ", SEPERATOR));
		free(token);
		i++;
	}
	temp_arr = double_free(temp_arr);
	return (new_nodes);
}

char	*replace_string(char *expanded, char	*str, int start, int end)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*new_line;

	before = ft_substr(str, 0, start - 1);
	after = ft_substr(str, end, ft_strlen(str) - end);
	temp = ft_strjoin(before, expanded);
	new_line = ft_strjoin(temp, after);
	free(temp);
	free(before);
	free(after);
	return (new_line);
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
	while (i < pos)
	{
		*head = (*(head))->next;
		if (i == pos - 2)
			prev_to_append = *head;
		i++;
	}
	i = 0;
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

void	double_dollar(t_token *tokens, t_token **head, int pos)
{
	char	*pid;
	size_t	i;
	t_token	*new_node;

	i = 0;
	pid = ft_itoa((int)getpid());
	while (i < ft_strlen(tokens->command))
	{
		if (ft_strlen(tokens->command + i) > 1 && tokens->command[i] == '$'
			&& tokens->command[i + 1] == '$')
		{
			i = ft_strlen(tokens->command) - ft_strlen(ft_strnstr \
				(tokens->command, "$$", ft_strlen(tokens->command)));
			new_node = create_nodes(pid, tokens->command, i + 1, i + 2);
			connect_nodes(new_node, pos, head);
			break ;
		}
		i++;
	}
	free(pid);
}

void	error_code_expansion(t_token *token, t_token **head, int pos)
{
	char	*error_code;
	size_t	i;
	t_token	*new_node;

	i = 0;
	error_code = ptr_check(ft_itoa(g_error_code));
	while (i < ft_strlen(token->command))
	{
		if (token->command[i + 1] && token->command[i] == '$'
			&& token->command[i + 1] == '?')
		{
			i = ft_strlen(token->command) - ft_strlen(ft_strnstr \
				(token->command, "$?", ft_strlen(token->command)));
			new_node = create_nodes(error_code, token->command, i + 1, i + 2);
			connect_nodes(new_node, pos, head);
			break ;
		}
		i++;
	}
	free(error_code);
}

void	expander(t_token **tokens, t_envepval *my_env)
{
	t_token	*head;
	int		i;
	int		old_pos;
	t_type	prev_type;
	bool	move_ptr;

	i = 0;
	head = *tokens;
	prev_type = SEPERATOR;
	while (*tokens)
	{
		move_ptr = true;
		if (if_tilde(tokens, prev_type))
			tilde_expansion((*tokens), my_env);
		if (((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strnstr((*tokens)->command, "$?", \
			ft_strlen((*tokens)->command)))
		{
			error_code_expansion(*tokens, &head, i);
			*tokens = head;
			old_pos = i;
			while (i--)
				*tokens = (*tokens)->next;
			i = old_pos;
		}
		if (((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strnstr((*tokens)->command, "$$", \
			ft_strlen((*tokens)->command)))
		{
			double_dollar(*tokens, &head, i);
			old_pos = i;
			*tokens = head;
			while (i--)
				*tokens = (*tokens)->next;
			i = old_pos;
		}
		if (((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strchr((*tokens)->command, '$')
			&& ft_strlen((*tokens)->command) != 1)
		{
			if (!dollar_expansion(*tokens, my_env, &head, i))
			{
				*tokens = head;
				old_pos = i;
				while (i--)
					*tokens = (*tokens)->next;
				i = old_pos;
			}
			else
			{
				move_ptr = false;
				*tokens = head;
				old_pos = i;
				i--;
				while (i-- >= 0)
					*tokens = (*tokens)->next;
				i = old_pos;
			}
		}
		if ((*tokens)->type == SEPERATOR)
			prev_type = SEPERATOR;
		else
			prev_type = DEFAULT;
		if (move_ptr)
		{
			*tokens = (*tokens)->next;
			i++;
		}
	}
	*tokens = head;
}
