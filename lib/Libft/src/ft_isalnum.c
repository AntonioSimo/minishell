/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 19:08:32 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/02 12:09:40 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function tests for any character if the characters is a letter 
or a number using the if statements*/

int	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// int	main(void)
// {
// 	printf("mine: %i\n", ft_isalnum('2'));
// 	printf("not mine: %i", isalnum(''));
// 	return (0);
// }
