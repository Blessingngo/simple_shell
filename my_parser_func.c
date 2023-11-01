#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 * @info: the info struct
 * @path: The path to the file.
 *
 * Return: 1 if executable, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters from a string.
 * @pathstr: The PATH string.
 * @start: The starting index.
 * @stop: The stopping index.
 *
 * Return: A pointer to the new buffer.
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[j++] = pathstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - Finds the full path of a
 * command in the PATH environment.
 * @info: info struct
 * @pathstr: Tthe PATH string
 * @command: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *command)
{
	int i = 0, start = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(command) > 2) && _starts_with(command, "./"))
	{
		if (is_cmd(info, command))
			return ((command));
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, start, i);
			if (!*path)

				_strcat(path, command);
			else
			{
				_strcat(path, "/");
					_strcat(path, command);
			}

				if (is_cmd(info, path))
					return (path);
			if (!pathstr[i])
				break;
			start = i;
		}
		i++;
	}

	return (NULL);
}
