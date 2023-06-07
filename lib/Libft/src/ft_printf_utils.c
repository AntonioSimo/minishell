/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 18:08:51 by asimone       #+#    #+#                 */
/*   Updated: 2023/03/08 17:32:46 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	ft_putnbr(int n)
{
	int	i;
	int	counter;

	counter = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		counter += write(1, "-", 1);
		if (counter < 0)
			return (-1);
		n = -n;
	}
	if (n >= 10)
		counter += ft_putnbr(n / 10);
	if (counter < 0)
		return (-1);
	i = n % 10 + 48;
	counter += write(1, &i, 1);
	return (counter);
}

int	ft_putnnbr(unsigned int n)
{
	unsigned int	i;
	int				counter;

	counter = 0;
	if (n >= 10)
		counter += ft_putnnbr(n / 10);
	if (counter < 0)
		return (-1);
	i = n % 10 + 48;
	counter += write(1, &i, 1);
	return (counter);
}

int	ft_itoh(unsigned long n, int check)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (n < 10)
		counter += ft_putchar(n + '0');
	else if (n >= 16)
	{
		counter += ft_itoh (n / 16, check);
		if (counter < 0)
			return (-1);
		counter += ft_itoh (n % 16, check);
	}
	else
	{
		if (check)
			i = n + 'W';
		else
			i = n + 55;
		counter += write(1, &i, 1);
	}
	return (counter);
}
