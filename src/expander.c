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
			*tokens = head;
			old_pos = i;
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
		if (*tokens && (*tokens)->type == SEPERATOR)
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
