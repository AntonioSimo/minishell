/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:52 by asimone           #+#    #+#             */
/*   Updated: 2023/11/23 14:30:51 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define  MINISHELL_H

# define GREEN "\x1b[32;01m"
# define RED "\x1b[31;01m"
# define YELLOW "\033[33;1m"
# define BOLD "\033[1m"
# define RESET  "\x1b[0m"
# define PATH_MAXSIZE 1024

// Exit_STATUS
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define TERMINATION_SIGINT 130
# define TERMINATION_SIGTERM 143

# include "../lib/Libft/include/libft.h"

#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#endif