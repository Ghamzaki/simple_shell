#include "shell.h"

/**
 * main - Entry point
 * @argc: ll
 * @argv: ll
 * Return: void
 */
int main(int argc, char **argv)
{
	command cmd;
	const char *program_name = (argc > 0) ? argv[0] : "";

	(void)argc;

	while (1)
	{
		print_prompt();
		read_input(&cmd);

		if (_strcmp(cmd.command, "exit") == 0)
		{
			break;
		}

		execute_command(&cmd, program_name);
	}
	return (0);
}
