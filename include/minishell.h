/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:52 by asimone           #+#    #+#             */
/*   Updated: 2023/08/16 20:08:29 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define  MINISHELL_H

# define GREEN "\x1b[32;01m"
# define RED "\x1b[31;01m"
# define YELLOW "\033[33;1m"
# define BOLD "\033[1m"
# define RESET  "\x1b[0m"
# define BUFFER_SIZE 1024

# include "../lib/Libft/include/libft.h"

# include <errno.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdio.h>

typedef enum e_type
{
	DEFAULT,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	REDIR_INPUT,
	HEREDOC,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APPEND,
	PIPE,
	SEPERATOR
}	t_type;

typedef enum e_fileflags
{
	INVALID = -1,
	INPUT,
	INPUT_HEREDOC,
	INPUT_HEREDOC_LIT,
	OUTPUT,
	OUTPUT_APP
}	t_fileflags;

typedef enum e_character_category
{
	CHAR_WHITESPACE = ' ',
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SINGLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_PARENTHESIS = ')',
	CHAR_NEW_LINE = '\n',
}	t_character_category;

/**
* @brief	This struct will return the user defined 
* @param arguments this is a pointer to the stirng ....
* @param command this is a pointer to the mlx image
* @param fd these are the fd for the Pipe.
* 					- fd_std[0]: Standard input.
*					- fd_std[1]: Standard output.
*					- fd_std[2]: Standard error output.
* @param rederection 
*/
typedef struct s_command
{
	char				**arguments;
	char				*command;
	int					fd[3];
	int					redirection;
	void				*content;
	struct s_command	*next;
}	t_command;


typedef struct s_file
{
	char		*name;
	t_fileflags	flag;
}	t_file;

typedef struct s_envepval
{
	char				*key;
	char				*val;
	struct s_envepval	*next;
}				t_envepval;

typedef struct s_token
{
	char			*command;
	t_type			type;
	struct s_token	*next;
}	t_token;

// lexer
int	ft_isspace(int c);
int	strlen_quoted(char *line, int position, t_type quotes_type);
t_type	quotes_type(char *line, int pos);
bool check_quotes(char *line);

//error
void	perror_exit(char *str);
void	strerror_exit();
void	*ptr_check(void *ptr);

void	parse(char *line);
void	lexer(char *line, t_envepval *my_env, char *or_home);

//tokenization
t_token	*create_token(char *string, t_type type);
void	tokenize_space(t_token **token_lst, char *line, int *i);
void	tokenize_symbols(t_token **token_lst, char *line, int *i);
void tokenize(char *line, t_token **token_lst);
//utils
void	print_list(t_token *token_lst);
int		find_equal(char *line);
t_envepval	*create_env_node(char *key, char *value);
void	tokenize_pipe(t_token **token_lst, int *i);
void	tokenize_redir_in(t_token **token_lst, int *i);
void	tokenize_redir_out(t_token **token_lst, int *i);
void	tokenize_redir_outapp(t_token **token_lst, int *i);
void	tokenize_heredoc(t_token **token_lst, int *i);


//expander
void	expander(t_token *tokens, t_envepval *my_env, char *or_home);
char	*find_expandable(t_envepval	*env, char	*key);

//list utils
void	lstadd_back(t_token **lst, t_token *new);
t_token	*lstnew(char *str, t_type type);
void	destroy_tokens(t_token	*tokens);


//env
void	set_env(t_envepval	**my_env, char **env);
void	print_my_env(t_envepval *my_env);

#endif