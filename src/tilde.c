/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:33:56 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 16:35:28 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	if_tilde(t_token **tokens, t_type prev_type)
{
	if (((*tokens)->type == DEFAULT && prev_type == SEPERATOR \
		&& !ft_strcmp((*tokens)->command, "~")) \
		|| !ft_strncmp((*tokens)->command, "~/", 2))
		return (0);
	return (1);
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

void	tilde_expansion(t_token *tokens, t_envepval *my_env)
{
	char	*home;
	char	*new_command;

	home = find_expandable(my_env, "HOME");
	if (ft_strlen(home) == 0)
	{
		free(home);
		home = ptr_check(find_home(my_env));
	}
	new_command = replace_string(home, tokens->command, 1, 1);
	free(tokens->command);
	tokens->command = ft_strdup(new_command);
	free(new_command);
	free(home);
}

char	*find_home(t_envepval *env)
{
	char	*username;
	char	*home;

	username = find_expandable(env, "USER");
	if (ft_strlen(username) > 0)
	{
		home = ptr_check(ft_strjoin("/home/", username));
		free(username);
		// printf("Home: %s\n", home);
		return (home);
	}
	free(username);
	username = find_expandable(env, "LOGNAME");
	if (ft_strlen(username) > 0)
	{
		home = ptr_check(ft_strjoin("/home/", username));
		free(username);
		// printf("Home: %s\n", home);
		return (home);
	}
	free(username);
	username = find_expandable(env, "USERNAME");
	home = ptr_check(ft_strjoin("/home/", username));
	// printf("Home: %s\n", home);
	free(username);
	return (home);
}
