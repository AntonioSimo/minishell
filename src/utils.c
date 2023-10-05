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

char	**push_str_2d(char **args, char *str)
{
	int	i;
	char	**new_args;
	
	i = 0;
	if (!str)
		return (args);
	if (!args && !str)
		return (NULL);
	if (args)
	{
		while (args[i])
			i++;
	}
	if (str)
		new_args = malloc(sizeof(char *) * (i + 2));
	else
		new_args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (args)
	{
		while (args[i])
		{
			new_args[i] = ptr_check(ft_strdup(args[i]));
			i++;
		}
	}
	if (str)
	{
		new_args[i] = ptr_check(ft_strdup(str));
		new_args[i + 1] = NULL;
	}
	else
		new_args[i] = NULL;
	if (args)
		args = double_free(args);
	return (new_args);
}

void	*ft_ptrdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	*double_free(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
	return (NULL);
}

char	*make_str_from_2d(char **args)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (args)
	{
		while (args[i])
		{
			str = ft_free_strjoin(str, args[i]);
			if (args[i + 1])
				str = ft_free_strjoin(str, " ");
			i++;
		}
	}
	return (str);
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_word(t_type type)
{
	if (type == DEFAULT || type == SINGLE_QUOTED
		|| type == DOUBLE_QUOTED)
		return (1);
	return (0);
}
