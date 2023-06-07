/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:11:24 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/14 10:13:14 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*The function writes n zeroed bytes to the string str. If n is zero, bzero() 
does nothing */

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

// int	main(void)
// {
// 	//int		i;
// 	int		x;
// 	char	str[50] = "1234";
// 	size_t	n;
// 	//char	nstr[50] = "1234";
// 	//size_t	a;

// 	//i = 0;
// 	x = 0;
// 	n = 2;
// 	//a = 2;
// 	ft_bzero(str, n);
// 	//bzero(nstr, a);
// 	//while (i != 50)
// 	//	printf("%c", nstr[i]);
// 	//	i++;
// 	//printf("\n"); /*printing the new lines*/
// 	while (x != 50)
// 		printf("%c", str[x]);
// 		x++;
// 	return (0);
// }
