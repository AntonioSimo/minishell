/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:57:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_print_message(char *command, char *str, char *error_message, int fd)
{
	write(fd, command, ft_strlen(command));
	write(fd, str, ft_strlen(str));
	write(fd, error_message, ft_strlen(error_message));
}
