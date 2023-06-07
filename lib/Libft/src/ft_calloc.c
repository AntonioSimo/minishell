/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 18:35:15 by asimone       #+#    #+#                 */
/*   Updated: 2023/02/06 13:58:00 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

//int main(void)
//{
//	int count;
//	int size;
//	void *ptr;

//	ptr = ft_calloc(SIZE_MAX, 2);
//	free(ptr);
//	return (0);
//}