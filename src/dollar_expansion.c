/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:40:39 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:45:01 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	dollar_expansion(t_token *tokens, t_envepval *my_env, t_token **head, int pos)
{
	char	*to_expand;
	char	*expanded;
	int		i;
	int		j;
	bool	brackets;
	t_token	*expanded_nodes;

	j = 0;
	i = 0;
	expanded = NULL;
	while (i < (int)ft_strlen(tokens->command))
	{
		if (tokens->command[i] == '$' && !tokens->command[i + 1])
			return (1);
		if (tokens->command[i] && tokens->command[i] == '$')
		{
			i++;
			if (tokens->command[i] == '{')
			{
				brackets = true;
				i++;
			}
			j = i;
			while (tokens->command[i] && char_to_expand(tokens->command[i]))
				i++;
			to_expand = ft_substr(tokens->command, j, i - j);
			expanded = find_expandable(my_env, to_expand);
			if (brackets)
			{
				j--;
				i++;
			}
			expanded_nodes = create_nodes(expanded, tokens->command, j, i);
			connect_nodes(expanded_nodes, pos, head);
			ft_free(to_expand);
			break ;
		}
		else
		{
			i++;
			while (tokens->command[i] && tokens->command[i] != '$')
				i++;
		}
	}
	if (ft_strlen(expanded) == 0)
	{
		return (1);
	}
	return (0);
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
