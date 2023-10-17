#include "minishell.h"

void	heredoc(t_redir_lst *temp, t_redir *redir)
{
	(void) redir;
	char *line;
	char *end_of_file = temp->file;
	int i = 0;

	if (end_of_file)
	{
		while (1)
		{
			line = readline("> ");
			printf("heredoc EOF: %s\n", end_of_file);
			printf("line: %s\n", line);
			if (line == NULL || ft_strcmp(end_of_file, line) == 0)
			{
				//free(line);
				printf("Ciao\n");
				break ;
			}
			free(line);
			//i++;
		}
	}
}