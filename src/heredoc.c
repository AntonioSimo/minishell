#include "minishell.h"

void	heredoc(char *file)
{
	char	*line;
	//printf("%s\n", file);
	char	*end_of_file = file;
	int		fd;

	fd = (open("/goinfre/file", O_RDWR | O_CREAT | O_TRUNC, 0644));
	printf("%i\n", fd);
	if (fd == -1) 
	{
		perror("Errore durante l'apertura del file");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		printf("%s\n", line);
		if (line == NULL || ft_strncmp(end_of_file, line, ft_strlen(end_of_file) + 1) == 0)
		{
			//free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}