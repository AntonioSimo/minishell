/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 19:39:26 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/02 12:23:20 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function tests for any printing character, 
including space using the if statements*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// int	main(void)
// {
// 	printf("mine: %i\n", ft_isprint(''));
// 	// printf("not mine: %i", isprint(''));
// 	return (0);
// }
