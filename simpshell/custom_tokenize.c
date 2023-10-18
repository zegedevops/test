#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_CMD_LEN 256
#define MAX_ARGS 10  /* Set an appropriate maximum number of arguments */

/**
 * custom_tokenize - Tokenizes the input command without using strtok
 * @cmd: The command to tokenize
 *
 * Return: An array of tokens (strings)
 */
char **custom_tokenize(char *cmd)
{
	int i = 0;
	int arg_count = 0;
	int len = strlen(cmd);
	char **tokens;
	int start = 0;
	int end;
	int token_len;
/*	tokens[arg_count] = NULL; */
	/*int j; */

	tokens = malloc((MAX_ARGS + 1) * sizeof(char *)); /* Allocate memory for tokens */
	if (!tokens)
	{
		perror("malloc");
			exit(EXIT_FAILURE);
	}
	/* Iterate through the command line and extract tokens */
	while (i < len)
	{
		/* skip leading spaces */
		while (i < len && cmd[i] == ' ')
			i++;
		if (i == len)
			break;

		start = i;
		/* find the end of the current token */
		while (i < len && cmd[i] != ' ')
			i++;
		end = i;
		/* Extract the token */
		token_len = end - start;
		tokens[arg_count] = malloc((token_len + 1) * sizeof(char));
		if (!tokens[arg_count])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strncpy(tokens[arg_count], &cmd[start], token_len);
		tokens[arg_count][token_len] = '\0';
		arg_count++;
		/* check if the maximum number of arguments is reached */
		if (arg_count >= MAX_ARGS)
			break;
	}
/*	for (j = 0; j < arg_count; j++)
    {
        free(tokens[j]);
    }
*/
	return (tokens);
}
