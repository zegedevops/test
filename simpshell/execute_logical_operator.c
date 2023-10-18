#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell.h"
#include <stdio.h>
#define MAX_SUB_COMMANDS 100

/**
 * execute_logical_operator - Executes a sub-command based on logical operators (&& and ||).
 *
 * @sub_cmd: The sub-command to be executed.
 * @prev_status: The status of the previous command execution.
 *
 * Return: The exit status of the sub-command execution.
 */
int execute_logical_operator(const char *sub_cmd, bool *exit_shell)
{
	int status = 0;
	bool and_operator = false;
	bool or_operator = false;
	char *sub_cmd_copy;
	int exit_shell_int = exit_shell ? 1 : 0;

	sub_cmd_copy= strdup(sub_cmd);
	if (sub_cmd_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	/* determine if the command is followed by && */
	if (sub_cmd_copy[strlen(sub_cmd_copy) -2] == '&' && sub_cmd_copy[strlen(sub_cmd_copy) - 1] == '&')
	{
		and_operator = true;
		sub_cmd_copy[strlen(sub_cmd_copy) - 2] = '\0'; /* remove the && */
	}

	/* Determine if the command is followed by || */
	if (sub_cmd_copy[strlen(sub_cmd_copy) - 2] == '|' && sub_cmd_copy[strlen(sub_cmd_copy) - 1] == '|')
	{
		or_operator = true;
		sub_cmd_copy[strlen(sub_cmd_copy) - 2] = '\0'; /* remove the || */
	}
	/* Execute the sub-command and get its exit status */
	 execute_shell_command(custom_tokenize(sub_cmd_copy), &exit_shell_int);
	if ((status == 0 && and_operator) || (status != 0 && or_operator))
	{
		*exit_shell = false;
	}
	return (status);
}
