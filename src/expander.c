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

static void	replace_string(char *expanded, char	*str, int start, int end)
{
	char	*before;
	char	*after;
	char	*temp;
	
	before = ft_substr(str, 0, start - 1);
	after = ft_substr(str, end, ft_strlen(str) - end);
	printf("before exp:%s \nexp:%s \n after exp:%s \n", before, expanded, after);
	temp = ft_strjoin(before, expanded);
	ft_free(str);
	str = ft_strjoin(temp, after);
	ft_free(temp);
	ft_free(before);
	ft_free(after);
	//printf("after exp: %s\n", str);
}

static void	update_token(t_token *tokens, t_envepval *my_env)
{
	//char	*command;
	char	*to_expand;
	char	*expanded;
	int i;
	int	j;

	j = 0;
	i = 0;
	(void)my_env;
	//command = ft_strdup(tokens->command);
	while(tokens->command[i])
	{
		//printf("tu");
		if (tokens->command[i] == '$')
		{
			i++;
			j = i;
			while (tokens->command[i] != '$' && tokens->command[i])
				i++;
			if (!tokens->command[i])
				i++;
			to_expand = ft_substr(tokens->command, j, i - j);	
			expanded = find_expandable(my_env, to_expand);
			//printf("expanded:%s \n",expanded);
			//printf("replace string from:%i to: %i", j , i);
			replace_string(expanded, tokens->command, j, i);
			//printf("str: %s\n", tokens->command);
			ft_free(to_expand);
			ft_free(expanded);
			i = 0;
		}
		else
			i++;
	}
	
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