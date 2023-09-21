/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/13 14:45:59 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_error_code;

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

char	*get_cmd_on_top(char *expanded)
{
	char	**temp_arr;
	char	*new_expanded;

	if (ft_strlen(expanded) == 0)
		return (expanded);
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
	free(temp);
	free(before);
	free(after);
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
		if (tokens->command[i] == '$' && !tokens->command[i + 1]) //to leave $ at the last position $USER$
			break ;
		if (tokens->command[i] == '$' && tokens->command[i + 1] //to skip $$ 
			&& tokens->command[i + 1] == '$')
				i += 2;
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
			expanded = get_cmd_on_top(expanded);
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
		}
		else
		{
			i++;
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
		free(home);
		home = ft_strdup(or_home);
	}
	new_command = replace_string(home, tokens->command, 1 , 1);
	free(tokens->command);
	tokens->command = ft_strdup(new_command);
	free(new_command);
	free(home);
}

void	double_dollar(t_token *tokens)
{
	char	*new_command;
	char	*pid;
	size_t		i;

	i = 0;
	pid = ft_itoa((int)getpid());
	while (ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)))
	{
		i = ft_strlen(tokens->command) - ft_strlen(ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)));
		new_command = replace_string(pid, tokens->command, i + 1, i + 2);
		free(tokens->command);
		tokens->command = ptr_check(ft_strdup(new_command));
		free(new_command);
	}
	free(pid);
}

void	error_code_expansion(t_token *token)
{
	char	*new_command;
	char	*error_code;
	int		i;

	i = 0;
	error_code = ptr_check(ft_itoa(g_error_code));
	while (ft_strnstr(token->command, "$?", ft_strlen(token->command)))
	{
		i = ft_strlen(token->command) - ft_strlen(ft_strnstr(token->command, "$?", ft_strlen(token->command)));
		new_command = replace_string(error_code, token->command, i + 1, i + 2);
		free(token->command);
		token->command = ptr_check(ft_strdup(new_command));
		free(new_command);
	}
	free(error_code);
}

void	expander(t_token *tokens, t_envepval *my_env, char *or_home)
{
	
	while (tokens)
	{
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strnstr(tokens->command, "$?", ft_strlen(tokens->command)))
			error_code_expansion(tokens);
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strchr(tokens->command, '$'))
			dollar_expansion(tokens, my_env);
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)))
			double_dollar(tokens);
		if (tokens->type == DEFAULT && tokens->command[0] == '~')
			tilde_expansion(tokens, my_env, or_home);
		tokens = tokens->next;
	}
}