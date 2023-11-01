#include "shell.h"

/**
 * _strcpy - function that copies a string
 * @dest: The destination string
 * @source: The source string
 *
 * Return: Pointer to the destination string
 */
char *_strcpy(char *dest, char *source)
{
	int i = 0;

	if (dest == source || source == NULL)
		return (dest);

	while (source[i])
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - function that duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return (NULL);

	for (length++; length--;)
		result[length] = *--str;

	return (result);
}

/**
 * _puts - function that prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - function that writes a character to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}
