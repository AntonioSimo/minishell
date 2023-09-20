#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *str;

    while (1)
    {
        str = readline("bash3.2$");
        if (str && *str != '\0')
        {
            printf("Valid!\n");
        }
        else if (!str)
        {
            printf("exit\n");
            break ;
        }
        else if (*str)
        {
            printf("it's not control D yoehoe!\n");
        }
    }
    return (0);
}