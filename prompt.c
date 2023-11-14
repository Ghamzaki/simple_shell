#include "shell.h"

/**
 * print_prompt - Displays a command prompt
 *
 * prints the shell prompt to the stdout.
 */
void print_prompt(void)
{
	_printf("Simpleshell$ ");
}

/**
 * read_input - Read and parse user input.
 * @cmd: A struct to store the parsed command and its args.
 *
 * this function reads a line of user input from the standard input,
 * parses it to separate the command and its arguments.
 */
void read_input(command *cmd)
{
	char input[MAX_COMMAND_LENGTH], *token;

	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		/* handle end of file */
		_printf("\nGoodbye!\n");
		exit(EXIT_SUCCESS);
	}

	input[strcspn(input, "\n")] = '\0';
	cmd->num_args = 0;

	token = strtok(input, " ");

	while (token != NULL && cmd->num_args < MAX_ARGS)
	{
		cmd->args[cmd->num_args] = _strdup(token);
		token = _strtok(NULL, " ");
		cmd->num_args++;
	}

	if (cmd->num_args > 0)
	{
		_strcpy(cmd->command, cmd->args[0]);
		cmd->args[cmd->num_args] = NULL;
	}
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
