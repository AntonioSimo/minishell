/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 19:27:08 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/02 12:11:20 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function tests for an ASCII character, which is any character 
between 0 and cotal 0117 inclusive using the if statements*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 0177);
}

// int	main(void)
// {
// 	printf("mine: %i\n", ft_isascii(''));
// 	printf("not mine: %i", isascii(''));
// 	return (0);
// }
