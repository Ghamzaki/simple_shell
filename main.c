#include "shell.h"

int main(void)
{
	command cmd;
	int i;

	while (1)
	{
		print_prompt();
		read_input(&cmd);

		if (cmd.num_args > 0)
		{
			execute_command(&cmd);
		}

		for (i = 0; i < cmd.num_args; i++)
		{
			free(cmd.args[i]);
		}
	}
	return (0);
}
