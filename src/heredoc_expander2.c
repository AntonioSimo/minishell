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

void	handle_error_code_heredoc(char **line, t_env *env)
{
	char	*error_code;
	size_t	i;
	char	*new_command;
	char	*temp;

	temp = ft_strdup(*line);
	i = 0;
	error_code = ptr_check(ft_itoa(env->exit_status));
	while (i < ft_strlen(temp))
	{
		if (temp[i + 1] && temp[i] == '$'
			&& temp[i + 1] == '?')
		{
			i = ft_strlen(temp) - ft_strlen(ft_strnstr \
				(temp, "$?", ft_strlen(temp)));
			new_command = replace_string(error_code, temp, i + 1, i + 2);
			free(temp);
			temp = ptr_check(ft_strdup(new_command));
			free(new_command);
			break ;
		}
		i++;
	}
	free_and_shuffle(temp, line, error_code);
}
