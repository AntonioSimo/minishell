/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 12:12:05 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/10 17:50:27 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

//int main(void)
//{
//	char s[50] = "Hello World!";
//	ft_putstr_fd(s, 1);
//	return (0);
//}