/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 18:02:04 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	strerror_exit(void)
{
	FILE	*fp;

	fp = fopen("file.txt", "r");
	if (!fp)
		printf("Error: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

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
