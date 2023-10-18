#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define MAX_INPUT_LEN 1024

/**
 * my_getline - function implementation of getline
 *
 * Return: A dynamically allocated string containing the input line
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1024

char *my_getline(void)
{
	char buffer[MAX_INPUT_LEN];
	int buffer_len = 0;
	char c;
	char *line;
	int i;

	while (1)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			break;
		}

		buffer[buffer_len++] = c;
		if (buffer_len >= MAX_INPUT_LEN - 1)
		{
			/* Buffer overflow prevention */
			fprintf(stderr, "input line too long\n");
			while ((c = getchar()) != '\n' && c != EOF)
				;
			break;
		}
	}

	if (buffer_len == 0 && c == EOF)
	{	
		return NULL;
	}
	line = malloc(buffer_len + 1);
	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < buffer_len; i++)
	{
		line[i] = buffer[i];
	}
	line[buffer_len] = '\0';
	return line;
}
