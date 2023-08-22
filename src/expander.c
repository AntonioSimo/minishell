/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/08/16 20:09:22 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	update_token(t_list	*tokens, t_list *my_env)
{
	//char *str;
	(void) my_env;
	(void) tokens;

	printf("jest $!\n");
}


static int	is_expandable(t_token	*token)
{
	if (token->type == DEFAULT || token->type == DOUBLE_QUOTED)
	{
		if (ft_strchr(token->command, '$'))
			return (1);
	}
	return (0);
}

void	expander(t_list	*tokens, t_list *my_env)
{
	while (tokens)
	{
		if (is_expandable(tokens->content))
			update_token(tokens, my_env);
		tokens = tokens->next;
	}
}