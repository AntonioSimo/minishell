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

char	**here_double_dollar(char **line)
{
	char	**new_command;
	char	*pid;
	size_t	i;
	int		j;

	j = 0;
	pid = ft_itoa((int)getpid());
	while (line[j])
	{
		i = 0;
		while (i < ft_strlen(line[j]))
		{
			if (ft_strlen(line[j] + i) > 1 && line[j][i] == '$'
				&& line[j][i + 1] == '$')
			{
				i = ft_strlen(line[j]) - ft_strlen(ft_strnstr \
					(line[j], "$$", ft_strlen(line[j])));
				new_command = make_2d_expanded(pid, line[j], i + 1, i + 2);
				line = append_strings(line, new_command, j);
				double_free(new_command);
				j = 0;
				break ;
			}
			i++;
		}
		j++;
	}
	free(pid);
	return (line);
}

char	**expand_here_dollar(int i, char **line, t_envepval *my_env, int pos)
{
	char	**new_command;
	char	*to_expand;
	char	*expanded;
	int		j;

	i++;
	j = i;
	while (line[pos][i] && char_to_expand(line[pos][i]))
		i++;
	to_expand = ft_substr(line[pos], j, i - j);
	expanded = find_expandable(my_env, to_expand);
	new_command = make_2d_expanded(expanded, line[pos], j, i);
	line = append_strings(line, new_command, pos);
	double_free(new_command);
	ft_free(to_expand);
	ft_free(expanded);
	return (line);
}

char	**here_dollar(char **line, t_envepval *my_env)
{
	int		i;
	int		j;

	j = 0;
	while (line[j])
	{
		i = 0;
		while (i < (int)ft_strlen(line[j]))
		{
			if (line[j][i] == '$' && !line[j][i + 1])
				break ;
			if (line[j][i] && line[j][i] == '$')
			{
				line = expand_here_dollar(i, line, my_env, j);
				j = 0;
			}
			else
			{
				i++;
				while (line[j][i] && line[j][i] != '$')
					i++;
			}
		}
		j++;
	}
	return (line);
}

char	*concat_input(char **str)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = NULL;
	while (str[i])
	{
		new_line = ft_free_strjoin(new_line, str[i]);
		i++;
	}
	return (new_line);
}

void	expand_heredoc(char **line, t_env *env)
{
	char	*dollar_ptr;
	char	**temp;

	temp = append_str(NULL, *line);
	free(*line);
	while (if_expand(temp))
	{
		dollar_ptr = find_dollar(temp);
		if (if_error_expansion_here(temp))
			temp = handle_error_code_heredoc(temp, env);
		if (if_double_dollar_here(temp))
			temp = here_double_dollar(temp);
		if (ft_strlen(dollar_ptr) > 1 && (char_to_expand(dollar_ptr[1]) || dollar_ptr[1] == '{'))
		{
			if (if_here_dollar(temp))
				temp = here_dollar(temp, env->env);
		}
	}
	*line = concat_input(temp);
	double_free(temp);
}
