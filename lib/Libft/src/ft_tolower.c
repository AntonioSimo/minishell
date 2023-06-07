/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:43:52 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/02 18:21:15 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function coverts an upper-case letter to 
the corresponding lower-case letter*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// int	main(void)
// {
// 	printf("mine: %c\n", ft_tolower('Z'));
// 	printf("not mine: %c", tolower('Z'));
// 	return (0);
// }
