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

static void	update_token(t_token *tokens, t_list *my_env)
{
	//char *str;
	(void) my_env;
	(void) tokens;

	printf("jest $!\n");
}

void	expander(t_token *tokens, t_list *my_env)
{
	while (tokens)
	{
		if (tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
		{
			if (ft_strchr(tokens->command, '$'))
				update_token(tokens, my_env);
		}
		tokens = tokens->next;
	}
}