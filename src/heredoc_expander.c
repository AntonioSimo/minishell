/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:15:54 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/12 13:46:54 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_error_code(char *line)
{
	if (ft_strnstr(line, "$?", ft_strlen(line)))
		return (0);
	return (1);
}

void	expand_heredoc(char **line, t_env *env)
{
	char	*temp;


	temp = ft_strchr(*line, '$');
	if (ft_strnstr(*line, "$?", ft_strlen(*line)))
		handle_error_code_heredoc(tokens, &(var->head), var, my_env);
	if (ft_strnstr(*line, "$$", ft_strlen(*line)))
		handle_double_dollar(tokens, &(var->head), var);
	if (ft_strlen(temp) > 1 && (char_to_expand(temp[1]) || temp[1] == '{'))
	{
		if (ft_strchr(*line, '$') && ft_strlen(*line) != 1)
		single_dollar(tokens, my_env->env, &(var->head), var);
	}
}