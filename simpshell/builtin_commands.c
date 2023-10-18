#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * my_setenv - Initialize a new environment variable or modify an existing one.
 * @name: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_setenv(const char *name, const char *value)
{
	int ret;

	ret = setenv(name, value, 1); /* use 1 to overwrite the variable if it already exists */
	if (ret != 0)
	{
		fprintf(stderr, "Error setting environment variable %s\n", name);
	}
	return ret;
}

/**
 * my_unsetenv - Remove an environment variable.
 * @name: The name of the environment variable to remove.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_unsetenv(const char *name)
{
	int ret = unsetenv(name);

	if (ret != 0)
	{
		fprintf(stderr, "Error unsetting environment variable %s\n", name);
	}
	return ret;
}	
