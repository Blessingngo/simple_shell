#include "shell.h"

/**
 * is_interactive - function that returns true if shell is in interactive mode
 * @info: struct address
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - function that checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
{
	if (*delim == c)
{
	return (1);
}
	delim++;
}
	return (0);
}

/**
 * is_alphabetic - function that checks for alphabetic character
 * @c: The character to input
 * Return: 1 if m is alphabetic, 0 otherwise
 */

int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}

/**
 * _atoi - function that converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
{
	if (s[i] == '-')
	sign *= -1;

	if (s[i] >= '0' && s[i] <= '9')
{
	flag = 1;
	result *= 10;
	result += (s[i] - '0');
}
	else if (flag == 1)
	flag = 2;
}
	if (sign == -1)
	output = -result;
	else
	output = result;
	return (output);
}
