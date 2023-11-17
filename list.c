#include "shell.h"

/**
 * handle_ls_command - Handles the execution of the 'ls' command
 * @cmd: A pointer struct containing the command and its args.
 * @program_name: name of the shell program.
 */
void handle_ls_command(command *cmd, const char *program_name)
{
	if (cmd->num_args == 1)
	{
		execute_ls_command(NULL);
	}
	else if (cmd->num_args == 2)
	{
		execute_ls_command(cmd->args[1]);
	}
	else
	{
		fprintf(stderr, "%s: ls: too many arguments\n", program_name);
	}
}

/**
 * execute_ls_command - Executes the 'ls'
 * command with optional directory argument
 *
 * @directory: The optional directory argument for 'ls'.
 */
void execute_ls_command(const char *directory)
{
	pid_t child_pid = fork();
	int status;

	if (child_pid == 0)
	{
		char *args[] = {"/bin/ls", NULL};

		if (directory != NULL)
		{
			args[2] = (char *)directory;
		}

		if (execve("/bin/ls", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (child_pid > 0)
	{
		waitpid(child_pid, &status, 0);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
