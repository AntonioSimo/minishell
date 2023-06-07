/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 14:32:04 by asimone       #+#    #+#                 */
/*   Updated: 2023/06/07 17:50:57 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main()
{
	char *str;
	
	while (1)
	{
		str = readline( GREEN BOLD "mustash> "RESET);
		add_history(str);
		printf("line = %s\n", str);
		free(str);
	}
    return 0;
}