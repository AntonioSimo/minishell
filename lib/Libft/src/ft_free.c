/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 18:00:55 by asimone       #+#    #+#                 */
/*   Updated: 2023/07/18 18:10:19 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}
