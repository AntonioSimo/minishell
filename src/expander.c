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

char	*find_expandable(t_envepval	*env, char	*key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key))
			&& !ft_strncmp(key, env->key, ft_strlen(key)))
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (ft_strdup(""));
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
	ft_free(temp);
	ft_free(before);
	ft_free(after);
	return (new_line);
}

static void	dollar_expansion(t_token *tokens, t_envepval *my_env)
{
	char	*new_command;
	char	*to_expand;
	char	*expanded;
	int i;
	int	j;

	j = 0;
	i = 0;
	(void)my_env;
	while(strchr(tokens->command, '$'))
	{
		if (tokens->command[i] == '$' && !tokens->command[i + 1])
			break ;
		if (tokens->command[i] == '$')
		{
			i++;
			j = i;
			while (tokens->command[i] && tokens->command[i] != '$')
				i++;
			to_expand = ft_substr(tokens->command, j, i - j);	
			expanded = find_expandable(my_env, to_expand);
			new_command = replace_string(expanded, tokens->command, j, i);
			ft_free(tokens->command);
			tokens->command = ft_strdup(new_command);
			ft_free(new_command);
			ft_free(to_expand);
			ft_free(expanded);
			i = 0;
		}
		else
		{
			while (tokens->command[i] && tokens->command[i] != '$')
				i++;
		}
	}
}

static void tilde_expansion(t_token *tokens, t_envepval *my_env)
{
	char	*home;
	char	*new_command;

	home = find_expandable(my_env, "HOME");
	new_command = replace_string(home, tokens->command, 1 , 1);
	ft_free(tokens->command);
	tokens->command = ft_strdup(new_command);
	ft_free(home);
}

void	expander(t_token *tokens, t_envepval *my_env)
{
	while (tokens)
	{
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strchr(tokens->command, '$'))
				dollar_expansion(tokens, my_env);
		if (tokens->type == DEFAULT && tokens->command[0] == '~')
			tilde_expansion(tokens, my_env);
		tokens = tokens->next;
	}
}