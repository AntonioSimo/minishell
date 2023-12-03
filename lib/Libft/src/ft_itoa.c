/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:00:40 by asimone       #+#    #+#                 */
/*   Updated: 2023/02/06 13:56:48 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countnbr(int nbr)
{
	int	count_digit;

	count_digit = 0;
	if (nbr >= 1)
	{
		while (nbr >= 1)
		{
			nbr /= 10;
			count_digit++;
		}
	}
	else
	{
		count_digit++;
		while (nbr <= -1)
		{
			nbr /= 10;
			count_digit++;
		}
	}
	return (count_digit);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ptr = (char *)malloc(ft_countnbr(n) + 1 * sizeof(char));
	if (ptr == 0)
		return (NULL);
	i = ft_countnbr(n);
	neg = 0;
	ptr[i] = '\0';
	if (n < 0)
	{
		neg = 1;
		n *= -1;
		ptr[0] = '-';
	}
	while (i > neg)
	{
		i--;
		ptr[i] = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}

// int main(void)
// {
// 	int a;
//	char *b;

// 	a = -143;
// 	b = ft_itoa(a);
//	printf("%s", b);
// 	//free(a);	
// 	//while(1)
// 	//	system("leaks a.out");
// }