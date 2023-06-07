/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 13:49:50 by asimone       #+#    #+#                 */
/*   Updated: 2022/10/14 18:22:29 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function converts a lower-case letter to 
the corresponding upper-case letter*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// int	main(void)
// {
// 	printf("mine: %c\n", ft_toupper('c'));
// 	printf("not mine: %c", toupper('c'));
// 	return (0);
// }
