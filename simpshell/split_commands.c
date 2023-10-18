#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "shell.h"

#define MAX_SUB_COMMANDS 100

/**
 * split_commands_by_logical_operators - Splits the input command into sub-commands
 *                                      based on logical operators
 * @cmd: The input command to split
 *
 * Return: An array of strings representing the sub-commands
 */

char **split_commands_by_logical_operators(const char *cmd, bool *exit_shell)
{
	char *sub_cmd_copy;
	char **sub_commands;
	int sub_cmd_index = 0;
	bool in_quotes = false;
	bool escape = false;
	int i;
	char current_char;
	int cmd_index = 0;

	sub_cmd_copy = strdup(cmd);
	if (sub_cmd_copy == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	sub_commands = (char **)malloc(sizeof(char *) * MAX_SUB_COMMANDS);
	if (sub_commands == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	/* initialize the first sub-command */
	sub_commands[sub_cmd_index] = (char *)malloc(strlen(cmd) + 1);
	if (sub_commands[sub_cmd_index] == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	/* Loop through each character in the input command */
	for (i = 0; sub_cmd_copy[i] != '\0'; i++)
	{
		current_char = sub_cmd_copy[i];
		if (current_char == '\\')
		{
			/* handle escape character */
			escape = !escape;
			if (escape)
			{
				continue;
			}
		}
		else if (current_char == '\'' || current_char == '\"')
		{
			if (!escape)
			{
				in_quotes = !in_quotes;
			}
		}
if (!in_quotes && (current_char == '&' || current_char == '|'))
        {
            if (!escape)
            {
                /* Null-terminate the previous sub-command */
                sub_commands[sub_cmd_index][cmd_index] = '\0';

                /* Move to the next sub-command */
                sub_cmd_index++;

                /* Reset the command index for the new sub-command */
                cmd_index = 0;

                /* Initialize the new sub-command */
                sub_commands[sub_cmd_index] = (char *)malloc(strlen(cmd) + 1);
                if (sub_commands[sub_cmd_index] == NULL)
                {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            /* Add the character to the sub-command */
            sub_commands[sub_cmd_index][cmd_index++] = current_char;
        }

        /* Reset escape flag after handling the character */
        escape = false;
    }

    /* Null-terminate the last sub-command */
    sub_commands[sub_cmd_index][cmd_index] = '\0';

    /* Call execute_logical_operator to handle logical operators for each sub-command */
    for (i = 0; i <= sub_cmd_index; i++)
    {
        execute_logical_operator(sub_commands[i], exit_shell);
    }

    /* Add a NULL pointer at the end of the sub-commands array to indicate the end */
    sub_commands[sub_cmd_index + 1] = NULL;

    free(sub_cmd_copy);
    return sub_commands;
}	
