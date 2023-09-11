/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:37:42 by asimone       #+#    #+#                 */
/*   Updated: 2022/10/17 10:52:30 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*This function copies n bytes from memory area src to memory area dst. 
If dst and src overlap, behavior is undefined.*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dcopy;
	unsigned char	*scopy;

	dcopy = (unsigned char *)dst;
	scopy = (unsigned char *)src;
	i = 0;
	if (dcopy == 0 && scopy == 0)
		return (0);
	if (dcopy == scopy && n == 0)
		return (dst);
	if (n == 0)
		return (0);
	while (i < n)
	{
		dcopy[i] = scopy[i];
		i++;
	}
	return (dst);
}

// int	main(void)
// {
// 	char src[50] = "123456789";
// 	char dst[50];
// 	char nsrc[50] = "123456789";
// 	char ndst[50];
// 	ft_memcpy(dst, src, 2);
// 	printf("mine: %s\n", (dst));
// 	//memcpy(ndst, nsrc, 2);
// 	//printf("not mine: %s\n", (ndst));
// 	return (0);
// }
