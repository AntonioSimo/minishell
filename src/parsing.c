/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/08/16 15:57:33 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse(char *line)
{
	char **splitted = ft_split(line, ' ');
	ft_printf("this is my line: %s\n", splitted[0]);
	exit(0);
}