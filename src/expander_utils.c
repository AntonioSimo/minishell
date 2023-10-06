/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:51:34 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:24:01 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

extern int g_error_code;

static void	handle_first_part(char *expanded, t_token **temp_node)
{
	int		i;
	t_token	*temp_expanded;
	t_token	*expanded_nodes;

	expanded_nodes = create_new_nodes(expanded);
	i = token_lst_size(expanded_nodes);
	while (i)
	{
		temp_expanded = expanded_nodes->next;
		expanded_nodes->next = NULL;
		push_token(temp_node, expanded_nodes);
		expanded_nodes = temp_expanded;
		i--;
	}
}

int	char_to_expand(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
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

