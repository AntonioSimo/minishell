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

int	is_double_dollar(t_token **tokens)
{
	if (((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
		&& ft_strnstr((*tokens)->command, "$$", \
		ft_strlen((*tokens)->command)))
		return (0);
	return (1);
}

int	is_single_dollar(t_token **tokens)
{
	char	*temp;

	temp = ft_strchr((*tokens)->command, '$');
	if (ft_strlen(temp) > 1 && (char_to_expand(temp[1]) || temp[1] == '{'))
	{
		if (((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strchr((*tokens)->command, '$')
			&& ft_strlen((*tokens)->command) != 1)
			return (0);
	}
	return (1);
}

int	is_error_code(t_token **tokens)
{
	if (((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
		&& ft_strnstr((*tokens)->command, "$?", \
		ft_strlen((*tokens)->command)))
		return (0);
	return (1);
}

void	handle_error_code(t_token **tokens, t_token **head, t_expander *var)
{
	error_code_expansion(*tokens, head, var->i);
	*tokens = *head;
	var->old_pos = var->i;
	while (var->i--)
		*tokens = (*tokens)->next;
	var->i = var->old_pos;
}

void	check_prev_token(t_token **tokens, t_expander *var)
{
	if (*tokens && (*tokens)->type == SEPERATOR)
		var->prev_type = SEPERATOR;
	else
		var->prev_type = DEFAULT;
}
