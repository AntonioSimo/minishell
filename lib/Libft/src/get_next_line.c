/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:42:41 by asimone           #+#    #+#             */
/*   Updated: 2023/09/13 15:34:30 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*update_line(char *old_line, char *buffer, int len)
{
	char	*new_line;
	int		old_line_size;
	int		i;

	old_line_size = ft_strlen(old_line);
	new_line = malloc(old_line_size + len + 1);
	if (!new_line)
	{
		free(old_line);
		return (NULL);
	}
	i = 0;
	while (i < old_line_size)
	{
		new_line[i] = old_line[i];
		i++;
	}
	i = -1;
	while (++i < len)
		new_line[old_line_size + i] = buffer[i];
	new_line[old_line_size + i] = '\0';
	free(old_line);
	old_line = NULL;
	return (new_line);
}

void	update_buffer(char *buffer, int nlpos)
{
	int	i;

	if (!buffer)
		return ;
	i = 0;
	while (buffer[nlpos + i])
	{
		buffer[i] = buffer[nlpos + i];
		i++;
	}
	buffer[i] = '\0';
}

int	check_for_nl(char *str)
{
	int	len;

	if (!str)
		return (-5);
	len = 0;
	while (str[len])
	{
		if (str[len] == '\n' && len + 1 == (int)ft_strlen(str))
		{
			return (-2);
		}
		if (str[len] == '\n')
			return (len);
		len++;
	}
	return (-1);
}

char	*read_line(char *buffer, int fd, char *line)
{
	int	read_size;

	read_size = 1;
	while (read_size > 0)
	{
		if (ft_strlen(buffer) && check_for_nl(buffer) == -2)
		{
			line = update_line(line, buffer, ft_strlen(buffer));
			buffer[0] = 0;
			return (line);
		}
		if (ft_strlen(buffer) && check_for_nl(buffer) >= 0)
		{
			line = update_line(line, buffer, check_for_nl(buffer) + 1);
			update_buffer(buffer, check_for_nl(buffer) + 1);
			return (line);
		}
		if (ft_strlen(buffer) && check_for_nl(buffer) == -1)
			line = update_line(line, buffer, ft_strlen(buffer));
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size >= 0)
			buffer[read_size] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	line = NULL;
	line = read_line(buffer, fd, line);
	if (!ft_strlen(buffer) || !line)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
