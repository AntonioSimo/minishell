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

int	if_expand(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strnstr(line[i], "$?", ft_strlen(line[i])) \
			|| ft_strnstr(line[i], "$$", ft_strlen(line[i])) \
			|| (ft_strchr(line[i], '$') && ft_strlen(line[i]) != 1))
			return (1);
		i++;
	}
	return (0);
}

char	*find_dollar(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(str[i], '$'))
			return (ft_strchr(str[i], '$'));
		i++;
	}
	return (NULL);
}

int	if_error_expansion_here(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strnstr(str[i], "$?", ft_strlen(str[i])))
			return (1);
		i++;
	}
	return (0);
}

int	if_double_dollar_here(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strnstr(str[i], "$$", ft_strlen(str[i])))
			return (1);
		i++;
	}
	return (0);
}

int	if_here_dollar(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(str[i], '$') && ft_strlen(str[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}