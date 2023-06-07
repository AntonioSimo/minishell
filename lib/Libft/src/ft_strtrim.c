/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:00:51 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/15 16:08:07 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_check(char s, char const *set)
{
	while (*set)
		if (*set++ == s)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	end;
	size_t	start;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL || *set == 0)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (ft_check(s1[start], set))
		start++;
	while (ft_check(s1[end - 1], set))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	str = ft_substr(s1, start, end - start);
	return (str);
}

// int main(void)
// {
//	char a[50] = "Hello World.";
//	printf("%s", ft_strtrim(a, "H"));
//	return (0);
// }