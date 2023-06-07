/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 13:08:44 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/02 12:22:26 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function tests for any character for which is uppercase or 
is lowercase using the if statements*/

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// int	main(void)
// {
// 	printf("mine: %i\n", ft_isalpha('4'));
// 	//printf("not mine: %i", isalpha(''));
// 	return (0);
// }
