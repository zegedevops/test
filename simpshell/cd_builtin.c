#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>

/**
 * cd_builtin - Handle the cd (change directory) builtin command.
 * @args: Array of strings containing the command and its arguments.
 */

void cd_builtin(char **args)
{
	int ret;
	char *dir;
	char *current_dir = NULL;
	size_t size = 0;
	
	/* handle cd command */
	if (args[1] == NULL)
	{
		/* no argument provided, change to the home directory */
	       dir = getenv("HOME");
       		if (dir == NULL)
		{
			fprintf(stderr, "Error: HOME environment variable not set\n");
			return;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		/* handle cd - */
		dir = getenv("OLDPWD");
		if (dir == NULL)
		{
			fprintf(stderr, "Error: OLDPWD environment variable not set\n");
			return;
		}
	}
	else
	{
		/* change to the specified directory */
		dir = args[1];
	}
	/* save the current directory in OLDPWD */
	current_dir = getcwd(current_dir, size);
	if (current_dir == NULL)
	{
		perror("getcwd");
		return;
	}
	setenv("OLDPWD", current_dir, 1);
	/* change to the specified directory */
	ret = chdir(dir);
	if (ret != 0)
	{
		perror("chdir");
		free(current_dir);
		return;
	}
	setenv("PWD", current_dir, 1);
	free(current_dir);
	return;
}
