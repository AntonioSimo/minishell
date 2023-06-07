/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/07 14:31:52 by asimone       #+#    #+#                 */
/*   Updated: 2023/06/07 18:36:32 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define  MINISHELL_H

#define GREEN "\x1b[32;01m"
#define RED "\x1b[31;01m"
#define YELLOW "\033[33;1m"
#define BOLD "\033[1m"
#define RESET  "\x1b[0m"

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#endif