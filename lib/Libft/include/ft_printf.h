/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 13:31:04 by asimone       #+#    #+#                 */
/*   Updated: 2023/03/01 18:21:25 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

int		ft_itoh(unsigned long n, int check);
int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putnnbr(unsigned int n);
int		ft_putstr(char *s);
size_t	ft_strlen(const char *s);

#endif