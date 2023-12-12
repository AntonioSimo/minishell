/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:39:33 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/04 13:43:21 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	find_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*access_path(char *cmd, char **paths)
{
	char	*part_path;
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		part_path = ptr_check(ft_strjoin(paths[i], "/"));
		path = ptr_check(ft_strjoin(part_path, cmd));
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				return (path);
			else
			{
				ft_print_message("mustash: ", cmd, \
				": Permission denied\n", STDERR_FILENO);
				exit (126);
			}
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char *envp)
{
	char	**paths;
	char	*path;

	paths = ft_split(envp, ':');
	free(envp);
	path = access_path(cmd, paths);
	double_free(paths);
	return (path);
}

void	*double_free(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i] != NULL)
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
	return (NULL);
}
