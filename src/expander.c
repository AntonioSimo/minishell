/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/06 13:27:19 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	char_to_expand(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

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

char	*remove_spaces(char *expanded)
{
	char	**temp_arr;
	char	*new_expanded;

	temp_arr = ptr_check(ft_split(expanded, ' '));
	expanded = ft_free(expanded);
	new_expanded = ptr_check(make_str_from_2d(temp_arr));
	return (new_expanded);
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
	int 	i;
	int		j;
	bool	brackets;

	j = 0;
	i = 0;
	(void)my_env;
	while(i < (int)ft_strlen(tokens->command))
	{
		if (tokens->command[i] == '$' && !tokens->command[i + 1])
			break ;
		if (tokens->command[i] == '$')
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
			//if (i > j)
			//{
				to_expand = ft_substr(tokens->command, j, i - j);	
				expanded = find_expandable(my_env, to_expand);
				expanded = remove_spaces(expanded);
				if (brackets) //to get rid of the {}
				{
					j--;
					i++;
				}
				new_command = replace_string(expanded, tokens->command, j, i);
				ft_free(tokens->command);
				tokens->command = ft_strdup(new_command);
				ft_free(new_command);
				ft_free(to_expand);
				ft_free(expanded);
				i = 0;
				brackets = false;
			//}
		}
		else
		{
			while (tokens->command[i] && tokens->command[i] != '$')
				i++;
		}
	}
}

static void tilde_expansion(t_token *tokens, t_envepval *my_env, char *or_home)
{
	char	*home;
	char	*new_command;

	home = find_expandable(my_env, "HOME");
	if (ft_strlen(home) == 0)
	{
		ft_free(home);
		home = ft_strdup(or_home);
	}
	new_command = replace_string(home, tokens->command, 1 , 1);
	ft_free(tokens->command);
	tokens->command = ft_strdup(new_command);
	ft_free(home);
}

void	expander(t_token *tokens, t_envepval *my_env, char *or_home)
{
	while (tokens)
	{
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strchr(tokens->command, '$'))
				dollar_expansion(tokens, my_env);
		else if (tokens->type == DEFAULT && tokens->command[0] == '~')
				tilde_expansion(tokens, my_env, or_home);

		tokens = tokens->next;
	}
}