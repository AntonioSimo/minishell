#include	"include/minishell.h"

void	fork_test()
{
    char *args[] = { "ls", "-la", NULL };
    char *env[] = { NULL };

    if (execve("/bin/ls", args, env) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // This code will not be reached if execve is successful
    printf("This won't be printed\n");



	int a;
	pid_t pid = fork();

	a = 5;
	//printf("fork returned: %d\n", pid);
	if (pid < 0)
	{
		printf("Fork Failed");
		return;
	}
	if (pid == 0)
	{
		fork();
		printf("We are the kids where the commands will be executed\n");
		//printf("This line is from child, a is %d\n", a);
		//printf("fork returned: %d\n", a);
	}
	else
	{
		printf("I am the main thread\n");
		//printf("This line is from child, a is %d\n", a);
	}
}

int	main()
{
	int pid;

	pid = fork();
	if (pid == 0)
		fork_test();
	else
		wait(NULL);
	printf("only in the main because the child died\n");
}