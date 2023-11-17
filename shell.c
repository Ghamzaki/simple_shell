#include "shell.h"

/**
 * execute_command - Execute a command in both current dir. and path
 * @cmd: A pointer struct containing the command and its args.
 * @program_name: name of the shell program.
 */
void execute_command(command *cmd, const char *program_name)
{
	if (access(cmd->command, F_OK) == 0)
	{
		execute_cwd(cmd);
	}
	else
	{
		execute_command_in_path(cmd, program_name);
	}
}

/**
 * execute_cwd - Execute a command in the current dir.
 * @cmd: A pointer to a command struct and args
 */
void execute_cwd(command *cmd)
{
	pid_t child_pid = fork();
	int status;

	if (child_pid == 0)
	{
		char *envp[] = {NULL};

		if (execve(cmd->command, cmd->args, envp) == -1)
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
 * execute_command_in_path - Execute a command
 * in the directories listed in PATH
 *
 * @cmd: A pointer struct containing the command and its args.
 * @program_name: name of the shell program.
 */
void execute_command_in_path(command *cmd, const char *program_name)
{
	if (access(cmd->command, F_OK) == 0)
	{
		execute_cwd(cmd);
		return;
	}

	fprintf(stderr, "%s: 1: %s: not found\n", program_name, cmd->command);
}

/**
 * execute_command_in_single_path - Execute a command in a single PATH
 * @cmd: A pointer struct containing the command and its args.
 * @path: The path to execute the command.
 */
void execute_command_in_single_path(command *cmd, const char *path)
{
	char *full_path = construct_full_path(cmd->command, path);

	if (access(full_path, F_OK) == 0)
	{
		execute_child_process(full_path, cmd->args);
	}
	free(full_path);
}

/**
 * construct_full_path - Construct the full
 * path for a command in a given directory
 *
 * @command: The command to execute.
 * @directory: The directory to search for the command.
 *
 * Return: A dynamically allocated string containing the full path.
 */
char *construct_full_path(const char *command, const char *directory)
{
	size_t full_path_length = _strlen(directory) + 1 + _strlen(command) + 1;
	char *full_path = malloc(sizeof(char) * full_path_length);

	if (full_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	snprintf(full_path, full_path_length, "%s/%s", directory, command);
	return (full_path);
}
