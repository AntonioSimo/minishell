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
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
	SEPERATOR,
	UNCLOSED
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
	char		*key;
	char		*val;
}				t_envepval;

typedef struct s_token
{
	char	*command;
	t_type	type;
}	t_token;

// pwd command
void	get_current_working_dir(void);

// cd command
int execute_cd(char *arg);

// ls command
int	execute_ls(char **environment);

// lexer
int	ft_isspace(int c);

//error
void	perror_exit(char *str);
void	strerror_exit();

#endif