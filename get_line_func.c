#include "shell.h"

/**
 * input_buf - Function that Read and buffer chained commands
 * @info: Parameter struct
 * @buf: Address of the buffer
 * @len: Address of length variable
 *
 * Return: Bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
	read_bytes = getline(buf, &len_p, stdin);
#else
	read_bytes = _getline(info, buf, &len_p);
#endif
	if (read_bytes > 0)
	{
		if ((*buf)[read_bytes - 1] == '\n')
		{
			(*buf)[read_bytes - 1] = '\0';
			read_bytes--;
		}
		info->linecount_flag = 1;
		_remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		if (_strchr(*buf, ';'))
		{
		*len = read_bytes;
		info->cmd_buf = buf;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - Function that Get a line excluding the newline
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, k, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = input_buf(info, &buf, &len);
	if (read_bytes == -1)
	return (-1);
	if (len)
	{
	k = i;
	p = buf + i;

	check_chain(info, buf, &k, i, len);
	while (k < len)
	{
		if (is_chain(info, buf, &k))
		break;
		k++;
	}

	i = k + 1;
	if (i >= len)
	{
		i = len = 0;
		info->cmd_buf_type = CMD_NORM;
	}

	*buf_p = p;
	return (strlen(p));
	}

	*buf_p = buf;
	return (read_bytes);
}

/**
 * read_buf - Function that Reads a buffer.
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 *
 * Return: read_bytes
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t read_bytes = 0;

	if (*i)
	return (0);
	read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (read_bytes >= 0)
	*i = read_bytes;
	return (read_bytes);
}

/**
 * _getline - Get the next line of input from STDIN.
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer, if not NULL
 *
 * Return: The Result.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t read_bytes = 0, result = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
	result = *length;
	if (i == len)
	i = len = 0;

	read_bytes = read_buf(info, buf, &len);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
	return (-1);

	c = _strchr(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, result, result ? result + j : j + 1);
	if (!new_p)
	return (p ? free(p), -1 : -1);

	if (result)
		_strncat(new_p, buf + i, j - i);
	else
		_strncpy(new_p, buf + i, j - i + 1);

	result += j - i;
	i = j;
	p = new_p;

	if (length)
	*length = result;
	*ptr = p;
	return (result);
}

/**
 * sigintHandler - Blocks Ctrl-C
 * @sig_num: The signal number
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
