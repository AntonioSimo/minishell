#include "../include/minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

t_token	*create_token(char *string, t_type type)
{
	t_token	*token;

	token = ptr_check(malloc(sizeof(t_token)));
	token->command = ptr_check(ft_strdup(string));
	token->type = type;
	return (token);
}



int	find_equal(char *line)
{
	int	i;
	
	i = 0;
	while(line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_path(char *cmd, char *envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	
	paths = ft_split(envp, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		// printf("checking path %s\n", path);
		if (access(path, F_OK) == 0)
		{
			// printf("return %s\n", path);
			return (path);
		}
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}