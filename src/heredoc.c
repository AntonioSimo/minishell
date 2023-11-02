/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:57:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *file)
{
	char	*line;
	char	*end_of_file;
	int		fd1;
	int		fd2;

	end_of_file = file;
	fd1 = (open("/tmp/file", O_CREAT | O_RDWR | O_TRUNC, 0644));
	if (fd1 == -1)
	{
		perror("Errore durante l'apertura del file");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL || \
		ft_strncmp(end_of_file, line, ft_strlen(end_of_file)) == 0)
		{
			free(line);
			break ;
		}
		write(fd1, line, ft_strlen(line));
		write(fd1, "\n", 1);
		free(line);
	}
	fd2 = open("/tmp/file", O_RDONLY, 0644);
	close(fd1);
	return (fd2);
}
