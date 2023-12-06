/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:15:54 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 13:46:54 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_double_dollar(char **line)
{
	char	*new_command;
	char	*pid;
	size_t	i;
	char	*temp;

	temp = ptr_check(ft_strdup(*line));
	free(*line);
	i = 0;
	pid = ft_itoa((int)getpid());
	while (ft_strnstr(temp, "$$", ft_strlen(temp)))
	{
		i = ft_strlen(temp) - \
			ft_strlen(ft_strnstr(temp, "$$", ft_strlen(temp)));
		new_command = replace_string(pid, temp, i + 1, i + 2);
		free(temp);
		temp = ptr_check(ft_strdup(new_command));
		free(new_command);
	}
	*line = ptr_check(ft_strdup(temp));
	free(temp);
	free(pid);
}

static void	expand_here_dollar(int i, char **line, t_envepval *my_env)
{
	char	*new_command;
	char	*to_expand;
	char	*expanded;
	int		j;
	char	*temp;

	i++;
	temp = ptr_check(ft_strdup(*line));
	free(*line);
	j = i;
	while (temp[i] && char_to_expand(temp[i]))
		i++;
	to_expand = ft_substr(temp, j, i - j);
	expanded = find_expandable(my_env, to_expand);
	new_command = replace_string(expanded, temp, j, i);
	ft_free(temp);
	temp = ft_strdup(new_command);
	ft_free(new_command);
	ft_free(to_expand);
	ft_free(expanded);
	i = 0;
	*line = ptr_check(ft_strdup(temp));
	free(temp);
}

static void	here_dollar(char **line, t_envepval *my_env)
{
	int		i;
	char	*temp;

	temp = ptr_check(ft_strdup(*line));
	free(*line);
	i = 0;
	while (i < (int)ft_strlen(temp))
	{
		if (temp[i] == '$' && !temp[i + 1])
			break ;
		if (temp[i] && temp[i] == '$')
		{
			expand_here_dollar(i, &temp, my_env);
			i = 0;
		}
		else
		{
			i++;
			while (temp[i] && temp[i] != '$')
				i++;
		}
	}
	*line = ptr_check(ft_strdup(temp));
	free(temp);
}

void	expand_heredoc(char **line, t_env *env)
{
	char	*temp;

	while (ft_strnstr(*line, "$?", ft_strlen(*line)) \
		|| ft_strnstr(*line, "$$", ft_strlen(*line)) \
		|| (ft_strchr(*line, '$') && ft_strlen(*line) != 1))
	{
		temp = ft_strchr(*line, '$');
		if (ft_strnstr(*line, "$?", ft_strlen(*line)))
			handle_error_code_heredoc(line, env);
		if (ft_strnstr(*line, "$$", ft_strlen(*line)))
			here_double_dollar(line);
		if (ft_strlen(temp) > 1 && (char_to_expand(temp[1]) || temp[1] == '{'))
		{
			if (ft_strchr(*line, '$') && ft_strlen(*line) != 1)
				here_dollar(line, env->env);
		}
	}
}
