#include "../include/minishell.h"

void	get_current_working_dir(t_env *env)
{
	char	pwd[FILENAME_MAX + 1];
	char	*temp;

	ft_memset(pwd, 0, sizeof(pwd));
	temp = malloc(sizeof(char *) * ft_strlen(pwd) + 1);
	if (!temp)
		free(temp);
	temp = getcwd(pwd, sizeof(pwd));
		ft_printf("%s\n", temp);
	env->exit_status = SUCCESS;
}