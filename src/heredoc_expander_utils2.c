/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:15:54 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/12 12:16:35 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**append_str(char **array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!array && !str)
		return (NULL);
	if (array && !str)
		return (array);
	new_array = ptr_check(malloc((strlen_2d(array) + 2) * sizeof(char *)));
	i = 0;
	if (array)
	{
		while (array[i])
		{
			new_array[i] = ptr_check(ft_strdup(array[i]));
			i++;
		}
	}
	new_array[i] = ptr_check(ft_strdup(str));
	new_array[i + 1] = NULL;
	double_free(array);
	return (new_array);
}
