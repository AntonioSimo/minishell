/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:00:48 by asimone       #+#    #+#                 */
/*   Updated: 2023/02/06 13:37:32 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char	ft_test(unsigned int i, char c)
//{
//	char str = c + 1;
//	return (str);
//}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == NULL)
		return (NULL);
	str = ft_strdup(s);
	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}

//int main(void)
//{
//	char a[50] = "hello world.";
//	char *b;
//	printf("%s\n", a);
//	b = ft_strmapi(a, *ft_test);
//	printf("%s", b);
//	return (0);
//}