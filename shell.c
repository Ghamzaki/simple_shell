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
 * execute_command - Execute a command in a new process
 * @cmd: A struct containing the command and its args.
 *
 */
void execute_command(command *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		/* Child process */
		char *envp[] = {NULL};

		if (execve(cmd->command, cmd->args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (child_pid > 0)
	{
		/* Parent process */
		waitpid(child_pid, &status, 0);
	}
}
