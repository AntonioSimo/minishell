/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:33:56 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/04 13:38:12 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	if_tilde(t_token **tokens, t_expander	*var)
{
	if (!var->if_expand)
		return (1);
	if (((*tokens)->type == DEFAULT && var->prev_type == SEPERATOR \
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

	before = ptr_check(ft_substr(str, 0, start - 1));
	after = ptr_check(ft_substr(str, end, ft_strlen(str) - end));
	temp = ptr_check(ft_strjoin(before, expanded));
	new_line = ptr_check(ft_strjoin(temp, after));
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
	tokens->command = ptr_check(ft_strdup(new_command));
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
		printf("Home: %s\n", home);
		return (home);
	}
	free(username);
	username = find_expandable(env, "LOGNAME");
	if (ft_strlen(username) > 0)
	{
		home = ptr_check(ft_strjoin("/home/", username));
		free(username);
		return (home);
	}
	free(username);
	username = find_expandable(env, "USERNAME");
	home = ptr_check(ft_strjoin("/home/", username));
	free(username);
	return (home);
}
