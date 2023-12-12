/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 18:00:38 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_and_shuffle(char *temp, char **line, char *error_code)
{
	free(error_code);
	free(*line);
	*line = ft_strdup(temp);
	free(temp);
}

char	**make_2d_expanded(char *expanded, char	*str, int start, int end)
{
	char	*before;
	char	*after;
	char	**new_arr;

	new_arr = NULL;
	before = ptr_check(ft_substr(str, 0, start - 1));
	after = ptr_check(ft_substr(str, end, ft_strlen(str) - end));
	if (ft_strlen(before) > 0)
		new_arr = append_str(NULL, before);
	new_arr = append_str(new_arr, expanded);
	if (ft_strlen(after))
		new_arr = append_str(new_arr, after);
	free(before);
	free(after);
	return (new_arr);
}

char	**append_strings(char **line, char **extra_strings, int pos)
{
	char	**new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = ptr_check(malloc(sizeof(char *) * (strlen_2d(line) \
				+ strlen_2d(extra_strings))));
	while (i < pos)
	{
		new_line[i] = ptr_check(ft_strdup(line[i]));
		i++;
	}
	while (extra_strings[j])
	{
		new_line[i + j] = ptr_check(ft_strdup(extra_strings[j]));
		j++;
	}
	while (line[i + 1])
	{
		new_line[i + j] = ptr_check(ft_strdup(line[i + 1]));
		i++;
	}
	double_free(line);
	new_line[i + j] = NULL;
	return (new_line);
}

char	**handle_error_code_heredoc(char **line, t_env *env)
{
	char	*error_code;
	size_t	i;
	char	**new_command;
	int		j;

	j = 0;
	error_code = ptr_check(ft_itoa(env->exit_status));
	while (line[j])
	{
		i = 0;
		while (i < ft_strlen(line[j]))
		{
			if (line[j][i + 1] && line[j][i] == '$'
				&& line[j][i + 1] == '?')
			{
				i = ft_strlen(line[j]) - ft_strlen(ft_strnstr \
					(line[j], "$?", ft_strlen(line[j])));
				new_command = make_2d_expanded(error_code, line[j], i + 1, i + 2);
				line = append_strings(line, new_command, j);
				double_free(new_command);
				j = 0;
				break ;
			}
			i++;
		}
		j++;
	}
	free(error_code);
	return (line);
}
