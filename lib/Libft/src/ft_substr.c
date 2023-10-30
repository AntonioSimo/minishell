/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:44:43 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/15 16:06:17 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (s == 0)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start + 1;
	else
		len++;
	ptr = malloc((len) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s[start], len);
	return (ptr);
}

// void	f()
// {
// 	atexit(system);
// }

// int	main(void)
// {
// 	char a[50] = "Ciao sono Antonio.";
// 	char *b;
// 	int start = 0;
// 	size_t len = 5;
// 	b = ft_substr(a, start, len);
// 	printf("%s", b);
// 	// system("leaks a.out");
// }
