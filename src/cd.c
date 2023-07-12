#include "../include/minishell.h"
#define MAX_PATH 0

//void	execute_cd(char **args, char *path)
//{
//	pid_t	pid;
//	//char	**single_path;
//	char	*chdir_path;
//	char	*current_dir[MAX_PATH];
//	char	*last_dir[MAX_PATH];

//	if (getcwd(current_dir, sizeof current_dir + 1))
//		args = getenv("HOME");
//	//single_path = ft_split(path, ':');
//	//printf("%s", *single_path);
//	//if (!single_path)
//	//	exit(EXIT_FAILURE)
//	if (args == NULL)

//	pid = fork();
//	if (pid == 0)
//		chdir(args[1]);
//	if (!args)
//		chdir_path = getenv("HOME");
//	else if (chdir(args[1]))
//		printf("no such file or directory\n");
//}

char lastdir[MAX_PATH];  // initialized to zero

int execute_cd(char *arg) 
{
    char curdir[MAX_PATH];
    char path[MAX_PATH];

    if (getcwd(curdir, sizeof curdir)) 
	{
        /* current directory might be unreachable: not an error */
        *curdir = '\0';
    }
    if (arg == NULL) 
        arg = getenv("HOME");
    if (!strcmp(arg, "-")) 
	{
        if (*lastdir == '\0') 
		{
            fprintf(stderr, "no previous directory\n");
            return 1;
        }
        arg = lastdir;
    } 
	else 
	{
        /* this should be done on all words during the parse phase */
        if (*arg == '~') 
		{
            if (arg[1] == '/' || arg[1] == '\0') 
			{
                snprintf(path, sizeof path, "%s%s", getenv("HOME"), arg + 1);
                arg = path;
            } 
			else 
			{
                /* ~name should expand to the home directory of user with login `name` 
                   this can be implemented with getpwent() */
                fprintf(stderr, "syntax not supported: %s\n", arg);
                return 1;
            }
        }
    }
    if (chdir(arg)) 
	{
        fprintf(stderr, "chdir: %s: %s\n", strerror(errno), path);
        return 1;
    }
    strcpy(lastdir, curdir);
    return 0;
}