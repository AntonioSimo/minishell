/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:49:48 by asimone           #+#    #+#             */
/*   Updated: 2023/11/23 15:41:43 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*The function computes the length of the string using the while loop.*/

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str && str[count] != '\0')
		count++;
	return (count);
}

// int	main(void)
// {
// 	char	str[50];

// 	printf("mine: %zu\n", ft_strlen("Codam"));
// 	printf("not mine: %zu", strlen("Codam"));
// 	return (0);
// }
