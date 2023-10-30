/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 16:48:25 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/14 13:20:58 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srcsize;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (srcsize);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srcsize);
}

// int	main(void)
// {
// 	char dst[50] = "Ciao sono Antonio";
// 	// char dst1[50] = "Ciao sono Antonio";
// 	ft_strlcpy(dst, dst+2, -1);
// 	// strlcpy(dst1, dst1+2, -1);
// 	printf("%s\n", dst);
// 	// printf("%s", dst1);
// }