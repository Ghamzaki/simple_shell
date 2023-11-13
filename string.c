#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _printf - prints string to the stdout
 * @c: string to print
 *
 */
void _printf(const char *c)
{
	write(STDOUT_FILENO, c, _strlen(c));
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0, i;
	char *dup;

	while (str[len] != '\0')
	{
		len++;
	}

	dup = malloc(sizeof(char) * (len + 1));

	if (dup == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= len; i++)
	{
		dup[i] = str[i];
	}
	return (dup);
}

/**
 * _strtok - String tokenizer function
 * @str: string to tokenize
 * @delimiter: characters used as delimiters
 *
 * Return: A pointer to the next token found in the string
 * else NULL
 */
char *_strtok(char *str, const char *delimiter)
{
	static char *token;
	char *start, *end;

	if (str != NULL)
	{
		token = str;
	}

	start = token;
	if (start == NULL)
	{
		return (NULL);
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
