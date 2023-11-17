#include "shell.h"

/**
 * execute_child_process - Execute a command in a child process
 * @path: The full path of the command.
 * @args: The arguments for the command.
 */
void execute_child_process(const char *path, char *const args[])
{
	pid_t child_pid = fork();
	int status;

	if (child_pid == 0)
	{
		char *envp[] = {NULL};

		if (execve(path, args, envp) == -1)
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

/**
 * cmd_notfound - If comand is not found
 * @command: command which was not found
 * @program_name: name of the shell program
 */
void cmd_notfound(const char *command, const char *program_name)
{
	if (_strcmp(command, "ls") == 0)
	{
		fprintf(stderr, "%s: No such file or directory\n", program_name);
	}
	else
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
	}
}
