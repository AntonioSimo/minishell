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

// char	*ft_free_strjoin(char *s1, char *s2)
// {
// 	char	*str;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	str = malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (free(s1), free(s2), NULL);
// 	while (s1 && s1[i])
// 		str[j++] = s1[i++];
// 	i = 0;
// 	while (s2 && s2[i])
// 		str[j++] = s2[i++];
// 	str[j] = '\0';
// 	s1 = ft_free(s1);
// 	return (str);
// }

// char	*ft_read_file(int fd, char *buffer)
// {
// 	char	*text;
// 	int		x;

// 	x = 1;
// 	text = malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	if (!text)
// 		return (free(buffer), NULL);
// 	while (x > 0 && !ft_strchr(buffer, '\n'))
// 	{
// 		x = read(fd, text, BUFFER_SIZE);
// 		if (x == -1)
// 		{
// 			free(buffer);
// 			free(text);
// 			return (NULL);
// 		}
// 		if (x == 0)
// 			break ;
// 		text[x] = '\0';
// 		buffer = ft_strjoin(buffer, text);
// 		if (buffer == NULL)
// 			return (NULL);
// 	}
// 	free(text);
// 	return (buffer);
// }

// char	*ft_find_leftover(char *str)
// {
// 	char	*leftover;
// 	size_t	i;
// 	size_t	x;

// 	i = 0;
// 	x = 0;
// 	while (str && str[i] != '\n' && str[i] != '\0')
// 		i++;
// 	leftover = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
// 	if (!leftover)
// 		return (free(str), NULL);
// 	if (str[i] == '\n')
// 		i++;
// 	while (str && str[i] != '\0')
// 	{
// 		leftover[x] = str[i];
// 		i++;
// 		x++;
// 	}
// 	leftover[x] = '\0';
// 	return (free(str), leftover);
// }

// char	*ft_read_line(char	*str)
// {
// 	char	*to_read;
// 	size_t	i;

// 	i = 0;
// 	while (str && str[i] != '\n' && str[i] != '\0')
// 		i++;
// 	if (str && str[i] == '\n')
// 		i++;
// 	to_read = malloc((i + 1) * sizeof (char));
// 	if (!to_read)
// 		return (NULL);
// 	i = 0;
// 	while (str && str[i] != '\n' && str[i] != '\0')
// 	{
// 		to_read[i] = str[i];
// 		i++;
// 	}
// 	if (str && str[i] == '\n')
// 	{
// 		to_read[i] = '\n';
// 		i++;
// 	}
// 	to_read[i] = '\0';
// 	return (to_read);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*buffer[FOPEN_MAX];
// 	char		*line;

// 	if (BUFFER_SIZE < 1 && read(fd, 0, 0) < 0)
// 		return (NULL);
// 	buffer[fd] = ft_read_file(fd, buffer[fd]);
// 	if (!buffer[fd])
// 		return (NULL);
// 	line = ft_read_line(buffer[fd]);
// 	if (!line)
// 	{
// 		free(buffer[fd]);
// 		buffer[fd] = NULL;
// 		return (NULL);
// 	}
// 	buffer[fd] = ft_find_leftover(buffer[fd]);
// 	if (!ft_strlen(buffer[fd]))
// 	{
// 		free(buffer[fd]);
// 		buffer[fd] = NULL;
// 	}
// 	return (line);
// }


char	*ft_free_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (free(s1), free(s2), NULL);
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	s1 = ft_free(s1);
	return (str);
}

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