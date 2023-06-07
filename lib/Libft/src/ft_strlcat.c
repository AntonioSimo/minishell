/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 17:05:24 by asimone       #+#    #+#                 */
/*   Updated: 2023/02/06 13:54:47 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_or;

	j = 0;
	i = 0;
	if (dst)
		i = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= i)
		return (ft_strlen(src) + dstsize);
	len_or = i;
	while (src[j] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(src) + len_or);
}

//int main(void)
//{
//	char dst[50] = "This is Codam.";
//	char src[50] = "This is a coding school.";
//	ft_strlcat(dst, src, 25);
//	printf("%s", dst);
//	return (0);
//}