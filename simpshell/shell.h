#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>

char *get_path(const char *cmd);
void execute_shell_command(char **args, int *exit_shell);
char *my_getline(void);
char **custom_tokenize(char *cmd);
int my_setenv(const char *name, const char *value);
int my_unsetenv(const char *name);
void cd_builtin(char **args);
void execute_multiple_commands(char *cmd, int *exit_shell);
int execute_logical_operator(const char *sub_cmd, bool *exit_shell);
char **split_commands_by_logical_operators(const char *cmd, bool *exit_shell);
#endif /* SHELL_H */
