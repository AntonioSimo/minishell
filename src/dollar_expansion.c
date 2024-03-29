/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/11/23 16:13:09 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dollar	*set_var_dollar(int pos)
{
	t_dollar	*var;

	var = ptr_check(malloc(sizeof(t_dollar)));
	var->to_expand = NULL;
	var->expanded = NULL;
	var->i = 0;
	var->j = 0;
	var->brackets = false;
	var->pos = pos;
	return (var);
}

void	calc_len(t_token *tokens, t_dollar *var)
{
	if (tokens->command[var->i] && !ft_isdigit(tokens->command[var->i]))
	{
		while (tokens->command[var->i] && \
				char_to_expand(tokens->command[var->i]))
			var->i++;
	}
	else
		var->i++;
}

void	expand_token(t_token *tokens, t_dollar *var, t_token **head, \
					t_envepval *my_env)
{
	t_token	*expanded_nodes;

	var->i++;
	if (tokens->command[var->i] == '{')
	{
		var->brackets = true;
		var->i++;
	}
	var->j = var->i;
	calc_len(tokens, var);
	var->to_expand = ft_substr(tokens->command, var->j, var->i - var->j);
	var->expanded = find_expandable(my_env, var->to_expand);
	if (var->brackets)
	{
		var->j--;
		var->i++;
	}
	expanded_nodes = create_nodes(var->expanded, tokens, \
								var->j, var->i);
	connect_nodes(expanded_nodes, var->pos, head);
}

int	free_var(t_dollar *var)
{
	if (var->expanded)
		free(var->expanded);
	if (var->to_expand)
	{
		free(var->to_expand);
	}
	free(var);
	return (1);
}

int	dollar_expansion(t_token *tokens, t_envepval *my_env, \
					t_token **head, int pos)
{
	t_dollar	*var;

	var = set_var_dollar(pos);
	while (var->i < (int)ft_strlen(tokens->command))
	{
		if (tokens->command[var->i] == '$' && !tokens->command[var->i + 1])
			return (free_var(var));
		if (tokens->command[var->i] && tokens->command[var->i] == '$')
		{
			expand_token(tokens, var, head, my_env);
			break ;
		}
		else
		{
			var->i++;
			while (tokens->command[var->i] && tokens->command[var->i] != '$')
				var->i++;
		}
	}
	if (ft_strlen(var->expanded) == 0)
		return (free_var(var));
	free_var(var);
	return (0);
}
