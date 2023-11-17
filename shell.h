#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

/**
 * struct command - Represents a command with its arguments.
 *
 * @command: A character array storing the command itself.
 * @args: An An array of character pointers storing the
 * command arguments.
 * @num_args: The number of arguments in the args array.
 */

typedef struct command
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_ARGS];
	int num_args;
} command;

	/*func. string.c*/
int _strlen(const char *s);
void _printf(const char *c);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
char *_strtok(char *str, const char *delimiter);

	/*func. shell.c*/
void execute_command(command *cmd, const char *program_name);
void execute_cwd(command *cmd);
void execute_command_in_path(command *cmd, const char *program_name);
void execute_command_in_single_path(command *cmd, const char *path);
void execute_path(command *cmd, char *path, const char *program_name);
char *construct_full_path(const char *command, const char *directory);

	/*func. shell1.c*/
void execute_child_process(const char *path, char *const args[]);
void cmd_notfound(const char *command, const char *program_name);

	/*func. prompt.c*/
void print_prompt(void);
void read_input(command *cmd);
int _strcmp(const char *s1, const char *s2);

	/*func. list.c*/
void handle_ls_command(command *cmd, const char *program_name);
void execute_ls_command(const char *directory);
#endif
