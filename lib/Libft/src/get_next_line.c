/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:42:41 by asimone           #+#    #+#             */
/*   Updated: 2023/11/28 16:02:41 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_read_file(int fd, char *buffer)
{
	char	*text;
	int		x;

	x = 1;
	text = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!text)
		return (free(buffer), NULL);
	while (x > 0 && !ft_strchr(buffer, '\n'))
	{
		x = read(fd, text, BUFFER_SIZE);
		if (x == -1)
		{
			free(buffer);
			free(text);
			return (NULL);
		}
		if (x == 0)
			break ;
		text[x] = '\0';
		buffer = ft_strjoin(buffer, text);
		if (buffer == NULL)
			return (NULL);
	}
	free(text);
	return (buffer);
}

char	*ft_find_leftover(char *str)
{
	char	*leftover;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	while (str && str[i] != '\n' && str[i] != '\0')
		i++;
	leftover = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
	if (!leftover)
		return (free(str), NULL);
	if (str[i] == '\n')
		i++;
	while (str && str[i] != '\0')
	{
		leftover[x] = str[i];
		i++;
		x++;
	}
	leftover[x] = '\0';
	return (free(str), leftover);
}

char	*ft_read_line(char	*str)
{
	char	*to_read;
	size_t	i;

	i = 0;
	while (str && str[i] != '\n' && str[i] != '\0')
		i++;
	if (str && str[i] == '\n')
		i++;
	to_read = malloc((i + 1) * sizeof (char));
	if (!to_read)
		return (NULL);
	i = 0;
	while (str && str[i] != '\n' && str[i] != '\0')
	{
		to_read[i] = str[i];
		i++;
	}
	if (str && str[i] == '\n')
	{
		to_read[i] = '\n';
		i++;
	}
	to_read[i] = '\0';
	return (to_read);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;

	if (BUFFER_SIZE < 1 && read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_read_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_find_leftover(buffer[fd]);
	if (!ft_strlen(buffer[fd]))
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}

//int main(void)
//{
//	int fd1 = open("text1.txt", O_RDONLY);
//	int fd2 = open("text2.txt", O_RDONLY);
//	//int fd3 = open("text3.txt", O_RDONLY);
//	char	*str;
//	char	*str2;

//	while(str && str2)
//	{
//		str = get_next_line(fd1);
//		str2 = get_next_line(fd2);
//		if (str && str2)
//			printf("%s", str);
//			printf("%s", str2);
//		free(str);
//		free(str2);
//	}
//	close (fd1);
//	close (fd2);
//	//close (fd3);
//	return (0);
//}