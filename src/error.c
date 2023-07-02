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
