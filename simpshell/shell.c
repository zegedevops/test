#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_CMD_LEN 1024
#define MAX_ARGS 1

/**
 * display_shell_prompt - Display a simple shell prompt
 */
void display_shell_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", strlen("$ "));
}

/**
 * main - Entry point of the shell command line interpreter
 *
 * Return: 0 on success
 */
int main(void)
{
	char cmd[MAX_CMD_LEN];
	int exit_shell = 0;
	char *line;
	size_t line_len;

	while (!exit_shell)
	{
		display_shell_prompt(); /* Display the prompt */
	
		line = my_getline();
		if (line == NULL)
		{
			if (feof(stdin))
			{
			exit(EXIT_SUCCESS);
			}
			else
			{
				perror("my_getline");
				exit(EXIT_FAILURE);
			}
		}
	       line_len = strlen(line);
if (line_len > 0 && line[line_len - 1] == '\n') {
    line[line_len - 1] = '\0';
}	
		strncpy(cmd, line, MAX_CMD_LEN - 1);
		cmd[MAX_CMD_LEN - 1] = '\0';
		free(line);
		
		/* Execute the command(s) */
		execute_multiple_commands(cmd, &exit_shell);
	}
	return 0;
}
