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
 * struct Command - Represents a command with its arguments.
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

typedef void (*CommandHandler)(command *);

	/*func. string*/
void _printf(const char *c);
char *_strtok(char *str, const char *delimiter);
	/*func. shell*/
void print_prompt(void);
void read_input(command *cmd);
void execute_command(command *cmd);

#endif
