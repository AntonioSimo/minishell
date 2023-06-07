/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 13:47:50 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/02 12:12:09 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function tests for a decimal digit character using the if statements. 
!IT'S NOT THE SAME isnumber!*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// int	main(void)
// {
// 	printf("mine: %i\n", ft_isdigit('0'));
// 	printf("not mine: %i", isdigit(''));
// 	return (0);
// }
