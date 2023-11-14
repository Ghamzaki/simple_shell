#include "shell.h"

/**
 * main - Entry point
 *
 * Return: void
 */
int main(void)
{
	command cmd;

	while (1)
	{
		print_prompt();
		read_input(&cmd);

		if (_strcmp(cmd.command, "exit") == 0)
		{
			break;
		}

		execute_command(&cmd);
	}
	return (0);
}
