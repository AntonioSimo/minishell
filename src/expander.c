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

extern int	g_error_code;

t_expander	*set_var(void)
{
	t_expander	*var;

	var = ptr_check(malloc(sizeof(t_expander)));
	var->i = 0;
	var->prev_type = SEPERATOR;
	var->old_pos = 0;
	var->move_ptr = true;
	return (var);
}

void	single_dollar(t_token **tokens, t_envepval *my_env, \
						t_token **head, t_expander *var)
{
	if (!dollar_expansion(*tokens, my_env, head, var->i))
	{
		*tokens = *head;
		var->old_pos = var->i;
		while (var->i--)
			*tokens = (*tokens)->next;
		var->i = var->old_pos;
	}
	else
	{
		var->move_ptr = false;
		*tokens = *head;
		// if ((*tokens))
		// {
			var->old_pos = var->i;
			var->i--;
			while (var->i-- >= 0)
				*tokens = (*tokens)->next;
			var->i = var->old_pos;
		// }
	}
}

void	handle_double_dollar(t_token **tokens, t_token *head, t_expander *var)
{
	double_dollar(*tokens, &head, var->i);
	*tokens = head;
	var->old_pos = var->i;
	while (var->i--)
		*tokens = (*tokens)->next;
	var->i = var->old_pos;
}

void	expander(t_token **tokens, t_envepval *my_env)
{
	t_expander	*var;
	t_token		*head;

	head = *tokens;
	var = set_var();
	while (*tokens)
	{
		var->move_ptr = true;
		if (!if_tilde(tokens, var->prev_type))
			tilde_expansion((*tokens), my_env);
		if (!is_error_code(tokens))
			handle_error_code(tokens, head, var);
		if (!is_double_dollar(tokens))
			handle_double_dollar(tokens, head, var);
		if (!is_single_dollar(tokens))
			single_dollar(tokens, my_env, &head, var);
		check_prev_token(tokens, var);
		if (var->move_ptr)
		{
			*tokens = (*tokens)->next;
			var->i++;
		}
	}
	*tokens = head;
}
