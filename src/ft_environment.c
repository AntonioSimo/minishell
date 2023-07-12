#include "../include/minishell.h"

char* get_shell_env(const char* environment) 
{
    return getenv(environment);
}
