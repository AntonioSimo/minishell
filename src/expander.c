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

char	*find_expandable(char *str)
{
	int i;
	int	j;

	j = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
		i++;
	}
}

static void	update_token(t_token *tokens, t_envepval *my_env)
{
	char *str;
	(void) my_env;
	(void) tokens;

	str = find_expandable(tokens->command);
	printf("%s\n", tokens->command);
}

void	expander(t_token *tokens, t_envepval *my_env)
{
	while (tokens)
	{
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strchr(tokens->command, '$'))
				update_token(tokens, my_env);
		tokens = tokens->next;
	}
}