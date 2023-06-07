/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 18:44:49 by asimone       #+#    #+#                 */
/*   Updated: 2022/10/18 15:09:01 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	char			*nhaystack;

	nhaystack = (char *) haystack;
	i = 0;
	j = 0;
	if (haystack == NULL && len == 0)
		return (NULL);
	if (needle[j] == '\0')
		return (&nhaystack[i]);
	while (nhaystack[i] != '\0')
	{
		while (nhaystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return (&nhaystack[i]);
		}
		i++;
		j = 0;
	}
	return (NULL);
}

// int	main(void)
// {
// // 	const char 	needle[50] = "sx";
// // 	const char 	haystack[50] = "Ciao sono Antonio";
// // 	size_t		len;
// // 	char 		*ptr;

// // 	len = 20;
// // 	ptr = ft_strnstr(haystack, needle, len);
// // 	//ptr = strnstr(haystack, needle, len);
// // 	printf("mine: %s", ptr);
// // 	//printf("not mine: %s", ptr);
// // 	return (0);

// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	printf("%s",ft_strnstr(haystack, needle, 0));

// }