#include "unistd.h"

int main()
{
    char   *a[] = {"minishell", NULL};

    execve("minishell", a, a);
}
