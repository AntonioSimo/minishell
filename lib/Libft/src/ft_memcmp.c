/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:16:19 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/16 18:40:42 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*ns1;
	unsigned char		*ns2;

	ns1 = (unsigned char *) s1;
	ns2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (ns1[i] != ns2[i])
			return (ns1[i] - ns2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	s1[50] = "ABCDE";
// 	char	s2[50] = "ABCFG";
// 	size_t	n;
// 	int		a;
// 	int		b;

// 	n = 5;
// 	a = ft_memcmp(s1, s2, n);
// 	b = memcmp(s1, s2, n);
// 	printf("mine: %i\n", a);
// 	printf("not mine: %i", b);
// 	return (0);
// }
