/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 13:47:02 by asimone       #+#    #+#                 */
/*   Updated: 2023/03/12 13:06:53 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The function copies len bytes from string src to string dest. The two strings
may overlap. */

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*dcopy;
	unsigned char	*scopy;

	dcopy = (unsigned char *) dest;
	scopy = (unsigned char *) src;
	if (dcopy == 0 && scopy == 0)
		return (0);
	if (dcopy > scopy)
	{
		while (len > 0)
		{
			len--;
			dcopy[len] = scopy[len];
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}

// int	main(void)
// {
// 	char	src[50] = "aabbcc";
// 	char	dest[50] ="aabbcc";
// 	char	nsrc[50] = "aabbcc";
// 	char	ndest[50] ="aabbcc";
// 	ft_memmove(src, src, 6);
// 	printf("mine: %s\n", (src));
// 	memmove(nsrc, nsrc, 6);
// 	printf("not mine: %s", (nsrc));
// 	return (0);
// }
