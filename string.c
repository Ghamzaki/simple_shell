#include "shell.h"

/**
 * _printf - prints string to the stdout
 * @c: string to print
 *
 */
void _printf(const char *c)
{
	write(STDOUT_FILENO, c, strlen(c));
}

/**
 * _strtok -
 */
char *_strtok(char *str, const char *delimiter)
{
	static char *token = NULL;
	char *start, *end;

	start = (str != NULL) ? str : token;
	if (start == NULL)
	{
		return NULL;
	}

	end = strpbrk(start, delimiter);

	if (end != NULL)
	{
		*end = '\0';
		token = end + 1;
	}
	else
	{
		token = NULL;
	}
	return (start);
}
