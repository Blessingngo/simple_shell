#include "shell.h"

/**
 * _strncpy - function that copies a string
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The amount of characters to be copied
 *
 * Return: The copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 * _strncat - function that concatenates two strings
 * @dest: The first string
 * @src: The second string
 * @n: The amount of bytes to be maximally used
 *
 * Return: The concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - function that locates a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 *
 * Return: A pointer to the memory area s
 */
char *_strchr(char *s, int c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
