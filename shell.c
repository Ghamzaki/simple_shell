#include "shell.h"

/**
 * execute_command - Execute a command in both current dir. and path
 * @cmd: A pointer struct containing the command and its args.
 * @program_name: name of the shell program.
 */
void execute_command(command *cmd, const char *program_name)
{
	char *path, *token;

	if (access(cmd->command, F_OK) == 0)
	{
		execute_cwd(cmd);
	}
	else
	{
		path = getenv("PATH");
		if (path == NULL)
		{
			fprintf(stderr, "Error: PATH environment variable is not set.\n");
			return;
		}
		token = _strtok(path, ":");
		while (token != NULL)
		{
			execute_path(cmd, token);
			token = strtok(NULL, ":");
		}
		cmd_notfound(cmd->command, program_name);
	}
}

/**
 * execute_cwd - Execute a command in the current dir.
 * @cmd: A pointer to a command struct and args
 */
void execute_cwd(command *cmd)
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
	if (child_pid > 0)
	{
		/* Parent process */
		waitpid(child_pid, &status, 0);
	}
}

/**
 * execute_path - Execute a command in path
 * @cmd: A pointer to a command struct
 * @path: path to execute
 *
 */
void execute_path(command *cmd, char *path)
{
	size_t full_path_length;
	char *full_path;

	full_path_length = _strlen(path) + 1 + _strlen(cmd->command) + 1;
	full_path = malloc(sizeof(char) * full_path_length);
	if (full_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	snprintf(full_path, full_path_length, "%s/%s", path, cmd->command);
	if (access(full_path, F_OK) == 0)
	{
		pid_t child_pid;
		int status;

		child_pid = fork();
		if (child_pid == 0)
		{
			char *envp[] = {NULL};

			if (execve(full_path, cmd->args, envp) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (child_pid > 0)
		{
			waitpid(child_pid, &status, 0);
			return;
		}
	}
	free(full_path);
}

/**
 * cmd_notfound - If comand is not found
 * @command: command which was not found
 * @program_name: name of the shell program
 */
void cmd_notfound(const char *command, const char *program_name)
{
	 fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
}
