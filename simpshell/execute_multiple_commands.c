#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

/**
 * execute_multiple_commands - Execute multiple shell commands separated by ';'.
 * @cmd: Input command containing multiple commands separated by ';'.
 */
void execute_multiple_commands(char *cmd, int *exit_shell)
{
	char *command = NULL;
	char **commands = NULL;
	int i = 0;
	int num_commands = 0;
	char *ptr;
	char **command_args;
	int j;
	/* spilt the input command by ';' manually */
	for (ptr = cmd; *ptr != '\0'; ptr++)
	{
		if (*ptr == ';')
		{
			*ptr = '\0'; /* replace the ';' with null terminator */
			commands = realloc(commands, (num_commands + 1) * sizeof(char *));
			if (commands == NULL)
			{
				perror("realloc");
				return;
			}
			commands[num_commands] = command;
			num_commands++;
			command = NULL;
		}
		else
		{
			if (command == NULL)
			{
				command = ptr;
			}
		}
	}
	if (command != NULL)
	{
		commands = realloc(commands, (num_commands + 1) * sizeof(char *));
		if (commands == NULL)
		{
			perror("realloc");
			return;
		}
		commands[num_commands] = command;
		num_commands++;
	}
	/* Execute each individual command */
	for (i = 0; i < num_commands; i++)
	{
		command_args = custom_tokenize(commands[i]);
		execute_shell_command(command_args, exit_shell);
		for (j = 0; command_args[j] != NULL; j++)
		{
			free(command_args[j]);
		}
		free(command_args);
		i++;
	}
	free(commands);
}
		
