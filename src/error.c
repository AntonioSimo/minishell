#include "../include/minishell.h"

/**
* @brief	This function will display an error message corresponding to 
* the errno value
* @return 	EXIT_FAILURE	
*/
void	strerror_exit(void)
{
	FILE	*fp;

	fp = fopen("file.txt", "r");
	if (!fp)
		printf("Error: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

/**
* @brief	This function will display an error message corresponding to 
* the errno value
* @param	str custom error message
* @return 	EXIT_FAILURE	
*/
void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	*ptr_check(void *ptr)
{
	if (ptr != NULL)
		return (ptr);
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

//EXIT CODE
int	ft_exit_status(char *msg, char *cmd, int exit_code, int return_val)
{
	t_env env;

	if (msg)
	{
		if (cmd)
			printf("%s: %s\n", cmd, msg);
		else
			printf("%s\n", msg);
	}
	if (exit_code != ERROR)
		env.exit_status = exit_code;
	return (return_val);
}