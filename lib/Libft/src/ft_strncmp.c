/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 18:43:00 by asimone       #+#    #+#                 */
/*   Updated: 2022/10/17 15:30:13 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ns1;
	unsigned char	*ns2;

	ns1 = (unsigned char *) s1;
	ns2 = (unsigned char *) s2;
	i = 0;
	while (n != 0)
	{
		if (ns1[i] != ns2[i] || (ns1[i] == 0 || ns2[i] == 0))
			return (ns1[i] - ns2[i]);
		i++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	char	s1[50] = "Ciao";
// 	char	s2[50] = "Ciaoa	";
// 	size_t	n;
// 	int		a;
// 	int		b;

// 	n = 6;
// 	a = ft_strncmp(s1, s2, n);
// 	b = strncmp(s1, s2, n);
// 	printf("mine: %i\n", a);
// 	printf("not mine: %i", b);
// 	return (0);
// }
