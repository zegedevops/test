#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include <unistd.h>
#include <ctype.h> 

#define MAX_CMD_LEN 1024
#define MAX_ARGS 10
extern char **environ;

char *get_path(const char *cmd)
{
	char *path_env_copy = strdup(getenv("PATH")); /* Get the PATH environment variable */
	char *path_copy = strdup(path_env_copy); 
	char *path = strtok(path_copy, ":"); /* Tokenize the PATH variable by ':' */
	char *full_path = NULL;
	int path_len;
	char last_char;
	
	if (strcmp(cmd, "exit") == 0)
			{	
				free(full_path);
				return ("builtin");
			}
	if (strcmp(cmd, "setenv") == 0)
	{
		free(full_path);
		return ("builtin");
	}
	if (strcmp(cmd, "unsetenv") == 0)
	{
		free(full_path);
		return ("builtin");
	}
	if (strcmp(cmd, "cd") == 0)
	{
		free(full_path);
		return ("builtin");
	}
	while (path != NULL)
	{	
		path_len = strlen(path);
		last_char = path[path_len-1];
		full_path = malloc(strlen(path) + strlen(cmd) + 2); /* Allocate memory for the full path */
		if (full_path == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
		if (cmd[0] == '/')
		{
			strcpy(full_path, cmd);
		}
		else if (last_char =='/')
				{
					snprintf(full_path, path_len + strlen(cmd) + 1, "%s%s", path, cmd);
				}
				else
				{
					snprintf(full_path, path_len + strlen(cmd) + 2, "%s/%s", path, cmd);
	       	/* Concatenate the directory path and the command */
		}
		if (access(full_path, X_OK) == 0) /* Check if the file is executable */
			{
				free(path_env_copy);
				return (full_path);
			}	/* Return the full path if the file is executable */
		free(full_path); /* Free the memory if the file is not executable */
		path = strtok(NULL, ":"); /* Get the next directory in PATH */
	}
	free(path_env_copy);
	free (path_copy);
	free(full_path);
	return NULL; /* Return NULL if the command is not found in any directory listed in PATH */
}
/**
 * execute_shell_command - Execute a shell command
 * @cmd: The command to execute
 * @exit_shell: A pointer to the exit shell flag
 */
void execute_shell_command(char **args, int *exit_shell)
{
    char *path_copy = NULL;
    char **dirs;
    char cmd_path[MAX_CMD_LEN];
    int dir_index = 0;
    char *path;
    int i;
    int exit_status;


    path = get_path(args[0]);
    if (path == NULL)
    {
        printf("Error: PATH variable not set\n");
        return;
    }
    if (strcmp(args[0], "exit") == 0)
    {
	    if (args[1] != NULL)
	    {
		    i = 0;
		    while (args[1][i] != '\0')
		    {
			    if (!isdigit(args[1][i]))
			    {
				    fprintf(stderr, "Error: Invalid exit status\n");
				    return;
			    }
			    i++;
		    }
		    exit_status = atoi(args[1]);
		    exit(exit_status);
	    }
	    else
	    {
        	*exit_shell = 1; /* Set the exit shell flag */
	    }
	    return;
    }
    else if (strcmp(args[0], "setenv") == 0)
    {
	    if (args[1] == NULL || args[2] == NULL)
	    {
		    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		    return;
	    }
	    my_setenv(args[1], args[2]);
	    return;
    }
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return;
		}
		my_unsetenv(args[1]);
		return;
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		/* call cd_builtin function to handle cd command */
		cd_builtin(args);
		return;
	}
    else if (strcmp(args[0], "env") == 0)
    {
       /*  Print the environment variables */
        char **env = environ;
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
    }
    else
    {
        /* Check if the command exists in the PATH */
        /* path = get_path(args[0]);
        if (path == NULL)
        {
            printf("Error: PATH variable not set\n");
            return;
        } */
        path_copy = strdup(path);
        dirs = custom_tokenize(path_copy);
        while (dirs[dir_index] != NULL)
        {
            snprintf(cmd_path, MAX_CMD_LEN, "%s", dirs[dir_index]);
           /* i = 0;
            while (args[i] != NULL)
            {
                printf("%s ", args[i]);
                i++;
            }
            printf("\n"); */

            if (access(cmd_path, X_OK) == 0)
            {
                /* Execute the command */
                pid_t pid = fork();
                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                    execv(cmd_path, args);
                    perror("execv");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    int status;
                    waitpid(pid, &status, 0);
                    if (WIFEXITED(status))
                    {
                        int exit_status = WEXITSTATUS(status);
                        if (exit_status != 0)
                        {
                            printf("Command '%s' returned non-zero exit status %d\n", args[0], exit_status);
                        }
                    }
                    else if (WIFSIGNALED(status))
                    {
                        int signal_num = WTERMSIG(status);
                        printf("Command '%s' terminated by signal %d\n", args[0], signal_num);
                    }
                    else if (WIFSTOPPED(status))
                    {
                        int signal_num = WSTOPSIG(status);
                        printf("Command '%s' stopped by signal %d\n", args[0], signal_num);
                    } 
			return;
                }
                return;
            }
            dir_index++;
        }
    }
    free(path_copy);
    free(dirs);
    for (i = 0; args[i] != NULL; i++)
    {
	    free(args[i]);
    }
    free(args);
}
