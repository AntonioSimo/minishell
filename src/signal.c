#include "../include/minishell.h"

int g_signal;


void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
        ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
        rl_redisplay();
	}
}

void    sigquit_handler(int sig)
{
    char    *line;
    
    if (!line)
    {
        sig == SIGQUIT;
    }
    if (sig == SIGQUIT)
    {

    }
}