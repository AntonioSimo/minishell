#include "../include/minishell.h"

/**
* @brief	This function replicate the behavior of pwd command
* @param 	void This function doesn't need a param
* @return 	It will return the current working directory saved in the variable temp.
*/
void	get_current_working_dir(void)
{
	char	pwd[FILENAME_MAX + 1];
	char	*temp;

	ft_memset(pwd, 0, sizeof(pwd)); //initialize pwd to zero to not print weird char
	temp = malloc(sizeof(char *) * ft_strlen(pwd) + 1);
	if (!temp)
		free(temp);
	temp = getcwd(pwd, sizeof(pwd));
		ft_printf("%s\n", temp);
}


//almost done with this command