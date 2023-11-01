#include "shell.h"

/**
* **strtow - function that splits a string into words.
* Repeat delimiters are ignored
* @str: input string
* @d: the delimiter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow(char *str, char *d)
{
	int i, j, length, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
{
		if (!is_delim(str[i], d) &&
			(is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;
}
	if (numwords == 0)
		return (NULL);
	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
	return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
{
		while (is_delim(str[i], d))
			i++;
		length = 0;
		while (!is_delim(str[i + length], d) && str[i + length])
			length++;
		words[j] = malloc((length + 1) * sizeof(char));
		if (!words[j])
{
			for (length = 0; length < j; length++)
				free(words[length]);
			free(words);
			return (NULL);
}
		for (m = 0; m < length; m++)
			words[j][m] = str[i++];
		words[j][m] = 0;
}
	words[j] = NULL;
	return (words);
}
/**
* **strtow2 - function that splits a string into words
* @str: the input string
* @d: the delimiter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char *d)
{
	int i, j, length, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
{
		if ((str[i] != *d && str[i + 1] == *d) ||
			(str[i] != *d && !str[i + 1]) || str[i + 1] == *d)
			numwords++;
}
	if (numwords == 0)
		return (NULL);
	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
{
		while (str[i] == *d && str[i] != *d)
			i++;
		length = 0;
		while (str[i + length] != *d &&
			str[i + length] && str[i + length] != *d)
			length++;
		words[j] = malloc((length + 1) * sizeof(char));
		if (!words[j])
{
			for (length = 0; length < j; length++)
				free(words[length]);
			free(words);
			return (NULL);
}
		for (m = 0; m < length; m++)
			words[j][m] = str[i++];
		words[j][m] = 0;
}
	words[j] = NULL;
	return (words);
}
